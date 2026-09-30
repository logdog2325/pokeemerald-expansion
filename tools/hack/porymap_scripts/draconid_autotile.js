// Draconid Emerald – Porymap auto-tiling (trees, cliffs, water, paths, ground).
//
// Uses the rules learned from vanilla maps by tools/hack/mapgen/autotile.py
// (exported to autotile_rules.js). Register with
//   python3 tools/hack/porymap_scripts/register.py
//
// Tools menu:
//   Draconid: Auto-tile while painting (toggle, Ctrl+Shift+A)
//       Paint any tree/cliff/water/path/ground metatile; the 5x5 area around it is
//       re-tiled so edges and corners match.
//   Draconid: Re-auto-tile whole map
//   Draconid: Re-auto-tile rectangle...
//   Draconid: Fill rectangle with terrain...   (tree, cliff, water, path, ground, ...)
//
// Only maps whose tileset pair has a learned brush are touched.

import { BRUSHES } from "./autotile_rules.js";

const OTHER = "o";
const N8 = [[-1, -1], [0, -1], [1, -1], [-1, 0], [1, 0], [-1, 1], [0, 1], [1, 1]];
const N4 = [[0, -1], [-1, 0], [1, 0], [0, 1]];

let enabled = false;
let busy = false;

export function onProjectOpened(projectPath) {
    utility.registerToggleAction("draconidToggleAutotile", "Draconid: Auto-tile while painting", "Ctrl+Shift+A", false);
    utility.registerAction("draconidAutotileMap", "Draconid: Re-auto-tile whole map");
    utility.registerAction("draconidAutotileRect", "Draconid: Re-auto-tile rectangle...");
    utility.registerAction("draconidFillRect", "Draconid: Fill rectangle with terrain...");
}

export function currentBrush() {
    return BRUSHES[map.getPrimaryTileset() + "/" + map.getSecondaryTileset()];
}

function classAt(brush, x, y) {
    const c = brush.memberClass[String(map.getMetatileId(x, y))];
    return c === undefined ? OTHER : c;
}

function norm8(bits) {
    // 0 NW, 1 N, 2 NE, 3 W, 4 E, 5 SW, 6 S, 7 SE: diagonals only count with both orthogonals
    const b = bits.slice();
    if (!(b[1] && b[3])) b[0] = 0;
    if (!(b[1] && b[4])) b[2] = 0;
    if (!(b[6] && b[3])) b[5] = 0;
    if (!(b[6] && b[4])) b[7] = 0;
    return b.join("");
}

function keysFor(cls, ctx8, ctx4, px, py, parity) {
    const same8 = norm8(ctx8.map(c => (c === cls ? 1 : 0)));
    const same4 = ctx4.map(c => (c === cls ? "1" : "0")).join("");
    const p = "" + px + py;
    const keys = [
        `${cls}|c8=${ctx8.join("")}|p=${p}`,
        `${cls}|c8=${ctx8.join("")}`,
        `${cls}|c4=${ctx4.join("")}|p=${p}`,
        `${cls}|c4=${ctx4.join("")}`,
        `${cls}|m8=${same8}|p=${p}`,
        `${cls}|m8=${same8}`,
        `${cls}|m4=${same4}|p=${p}`,
        `${cls}|m4=${same4}`,
        `${cls}|p=${p}`,
    ];
    return parity ? keys : keys.filter(k => k.indexOf("|p=") < 0);
}

function neighbours(grid, x, y, w, h, offs) {
    const here = grid[y][x];
    return offs.map(([dx, dy]) => {
        const nx = x + dx, ny = y + dy;
        return (nx >= 0 && nx < w && ny >= 0 && ny < h) ? grid[ny][nx] : here;
    });
}

// Phase of the 2x2 pattern (trees): align to an anchor tile found near (x, y) but outside
// the rectangle being re-tiled (those cells are about to change); default (0, 0) like mapbuild.py.
function phaseFor(brush, cls, x, y, rect) {
    const anchor = brush.classes[cls] ? brush.classes[cls].anchor : null;
    if (anchor === null || anchor === undefined) return [0, 0];
    const w = map.getWidth(), h = map.getHeight();
    for (let r = 1; r <= 4; r++) {
        for (let dy = -r; dy <= r; dy++) {
            for (let dx = -r; dx <= r; dx++) {
                const nx = x + dx, ny = y + dy;
                if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
                if (rect && nx >= rect[0] && nx <= rect[2] && ny >= rect[1] && ny <= rect[3]) continue;
                if (map.getMetatileId(nx, ny) === anchor) return [((nx % 2) + 2) % 2, ((ny % 2) + 2) % 2];
            }
        }
    }
    return [0, 0];
}

function resolveCell(brush, grid, x, y, w, h, rect) {
    const c = grid[y][x];
    const cdef = brush.classes[c];
    if (!cdef) return null;
    const ctx8 = neighbours(grid, x, y, w, h, N8);
    const ctx4 = neighbours(grid, x, y, w, h, N4);
    const near = new Set(ctx8);
    const banned = new Set();
    for (const r of cdef.onlyNear) {
        if (!r.classes.some(k => near.has(k))) r.tiles.forEach(t => banned.add(t));
    }
    const [phx, phy] = phaseFor(brush, c, x, y, rect);
    const px = ((x - phx) % 2 + 2) % 2, py = ((y - phy) % 2 + 2) % 2;
    for (const k of keysFor(c, ctx8, ctx4, px, py, cdef.parity)) {
        const opts = brush.rules[k];
        if (!opts) continue;
        const ok = opts.filter(o => !banned.has(o[0]));
        if (ok.length) return ok[0];
    }
    return cdef.default;
}

function classGrid(brush) {
    // grid covering the whole map (neighbour lookups need context outside the rect)
    const w = map.getWidth(), h = map.getHeight();
    const g = [];
    for (let y = 0; y < h; y++) {
        const row = [];
        for (let x = 0; x < w; x++) row.push(classAt(brush, x, y));
        g.push(row);
    }
    return g;
}

export function autotileRect(x0, y0, x1, y1) {
    const brush = currentBrush();
    if (!brush) {
        utility.warn("Draconid auto-tile: no learned brush for " + map.getPrimaryTileset() + "/" + map.getSecondaryTileset());
        return 0;
    }
    const w = map.getWidth(), h = map.getHeight();
    const g = classGrid(brush);
    const rect = [Math.max(0, x0), Math.max(0, y0), Math.min(w - 1, x1), Math.min(h - 1, y1)];
    // resolve everything first, then write, so no cell sees a half-updated map
    const updates = [];
    for (let y = rect[1]; y <= rect[3]; y++) {
        for (let x = rect[0]; x <= rect[2]; x++) {
            if (g[y][x] === OTHER || !brush.classes[g[y][x]].paintable) continue;
            const blk = resolveCell(brush, g, x, y, w, h, rect);
            if (blk) updates.push([x, y, blk]);
        }
    }
    let changed = 0;
    busy = true;
    try {
        for (const [x, y, blk] of updates) {
            const cur = map.getBlock(x, y);
            if (cur.metatileId !== blk[0] || cur.collision !== blk[1] || cur.elevation !== blk[2]) {
                map.setBlock(x, y, blk[0], blk[1], blk[2], false, false);
                changed++;
            }
        }
    } finally {
        busy = false;
    }
    map.redraw();
    map.commit();
    return changed;
}

export function draconidToggleAutotile() {
    enabled = !enabled;
    utility.log("Draconid auto-tile while painting: " + (enabled ? "on" : "off"));
}

export function draconidAutotileMap() {
    const n = autotileRect(0, 0, map.getWidth() - 1, map.getHeight() - 1);
    utility.log("Draconid auto-tile: changed " + n + " block(s)");
}

function askRect(title) {
    const r = utility.getInputText(title, "Rectangle as x,y,width,height", "0,0," + map.getWidth() + "," + map.getHeight());
    if (!r.ok) return null;
    const v = r.input.split(",").map(s => parseInt(s.trim(), 10));
    if (v.length !== 4 || v.some(isNaN)) {
        utility.showError("Expected four numbers: x,y,width,height");
        return null;
    }
    return v;
}

export function draconidAutotileRect() {
    const v = askRect("Re-auto-tile rectangle");
    if (!v) return;
    const n = autotileRect(v[0], v[1], v[0] + v[2] - 1, v[1] + v[3] - 1);
    utility.log("Draconid auto-tile: changed " + n + " block(s)");
}

export function draconidFillRect() {
    const brush = currentBrush();
    if (!brush) {
        utility.showError("No learned brush for this tileset pair.");
        return;
    }
    const names = Object.keys(brush.classes).filter(k => brush.classes[k].paintable).map(k => brush.classes[k].name);
    const pick = utility.getInputItem("Fill with terrain", "Terrain class", names, 0, false);
    if (!pick.ok) return;
    const code = Object.keys(brush.classes).find(k => brush.classes[k].name === pick.input);
    const v = askRect("Fill rectangle with " + pick.input);
    if (!v) return;
    let [x0, y0, w, h] = v;
    if (brush.classes[code].anchor !== null && brush.classes[code].anchor !== undefined) {
        // whole 2x2 trees only
        x0 -= x0 % 2; y0 -= y0 % 2; w += w % 2; h += h % 2;
    }
    const d = brush.classes[code].default;
    busy = true;
    try {
        for (let y = y0; y < y0 + h; y++)
            for (let x = x0; x < x0 + w; x++)
                if (x >= 0 && y >= 0 && x < map.getWidth() && y < map.getHeight())
                    map.setBlock(x, y, d[0], d[1], d[2], false, false);
    } finally {
        busy = false;
    }
    autotileRect(x0 - 2, y0 - 2, x0 + w + 1, y0 + h + 1);
}

export function onBlockChanged(x, y, prevBlock, newBlock) {
    if (!enabled || busy) return;
    const brush = currentBrush();
    if (!brush) return;
    const c = brush.memberClass[String(newBlock.metatileId)];
    const was = brush.memberClass[String(prevBlock.metatileId)];
    if (c === undefined && was === undefined) return;
    autotileRect(x - 2, y - 2, x + 2, y + 2);
}
