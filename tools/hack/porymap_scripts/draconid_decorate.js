// Draconid Emerald – Porymap decoration helpers.
//
// Tools menu:
//   Draconid: Scatter grass tufts / flowers...   random decorations on open ground
//   Draconid: Tree border...                     ring of whole 2x2 trees around the map edge
//   Draconid: Scatter meteorite rocks...         boulders on open ground (Fallarbor tilesets)
//
// Decorations are only placed on cells whose 8 neighbours are the same terrain class,
// so edges drawn by the auto-tiler are never disturbed. Everything is one undo step.

import { BRUSHES } from "./autotile_rules.js";
import { autotileRect, currentBrush } from "./draconid_autotile.js";

// Decoration sets per terrain class name. Blocks are [metatile, collision, elevation].
const DECOR = {
    "gTileset_General/gTileset_Fallarbor": {
        ground: { tufts: [[0x29F, 0, 3], [0x2A7, 0, 3], [0x2EC, 0, 3], [0x2FC, 0, 3]], rocks: [[0x2AF, 1, 0], [0x2BF, 1, 0]] },
        grass: { tufts: [[0x002, 0, 3], [0x004, 0, 3]] },
    },
    "gTileset_General/gTileset_Petalburg": {
        grass: { tufts: [[0x002, 0, 3], [0x004, 0, 3]] },
    },
};

export function onProjectOpened(projectPath) {
    utility.registerAction("draconidScatter", "Draconid: Scatter grass tufts / flowers...");
    utility.registerAction("draconidTreeBorder", "Draconid: Tree border...");
    utility.registerAction("draconidRocks", "Draconid: Scatter meteorite rocks...");
}

function pairKey() {
    return map.getPrimaryTileset() + "/" + map.getSecondaryTileset();
}

function interiorCells(brush, className) {
    const code = Object.keys(brush.classes).find(k => brush.classes[k].name === className);
    const out = [];
    const w = map.getWidth(), h = map.getHeight();
    const cls = (x, y) => brush.memberClass[String(map.getMetatileId(x, y))];
    for (let y = 1; y < h - 1; y++) {
        for (let x = 1; x < w - 1; x++) {
            let ok = cls(x, y) === code;
            for (let dy = -1; ok && dy <= 1; dy++)
                for (let dx = -1; ok && dx <= 1; dx++)
                    if (cls(x + dx, y + dy) !== code) ok = false;
            if (ok) out.push([x, y]);
        }
    }
    return out;
}

function scatter(kind, defaultPercent) {
    const brush = currentBrush();
    const decor = DECOR[pairKey()];
    if (!brush || !decor) {
        utility.showError("No decoration set for " + pairKey());
        return;
    }
    const classes = Object.keys(decor).filter(c => decor[c][kind]);
    const pick = utility.getInputItem("Scatter", "On which terrain?", classes, 0, false);
    if (!pick.ok) return;
    const pct = utility.getInputNumber("Scatter", "Density (% of open cells)", defaultPercent, 0, 100, 0, 1);
    if (!pct.ok) return;
    const blocks = decor[pick.input][kind];
    let n = 0;
    for (const [x, y] of interiorCells(brush, pick.input)) {
        if (Math.random() * 100 < pct.input) {
            const b = blocks[Math.floor(Math.random() * blocks.length)];
            map.setBlock(x, y, b[0], b[1], b[2], false, false);
            n++;
        }
    }
    map.redraw();
    map.commit();
    utility.log("Draconid scatter: placed " + n + " block(s)");
}

export function draconidScatter() {
    scatter("tufts", 6);
}

export function draconidRocks() {
    scatter("rocks", 2);
}

export function draconidTreeBorder() {
    const brush = currentBrush();
    if (!brush) {
        utility.showError("No learned brush for " + pairKey());
        return;
    }
    const treeCode = Object.keys(brush.classes).find(k => brush.classes[k].name === "tree");
    if (!treeCode) {
        utility.showError("This brush has no 'tree' class.");
        return;
    }
    const t = utility.getInputNumber("Tree border", "Thickness in trees (1 tree = 2 tiles)", 1, 1, 4, 0, 1);
    if (!t.ok) return;
    const th = t.input * 2;
    const d = brush.classes[treeCode].default;
    const w = map.getWidth(), h = map.getHeight();
    for (let y = 0; y < h; y++)
        for (let x = 0; x < w; x++)
            if (x < th || y < th || x >= w - th - (w % 2) || y >= h - th - (h % 2))
                map.setBlock(x, y, d[0], d[1], d[2], false, false);
    autotileRect(0, 0, w - 1, h - 1);
}
