# Draconid Emerald – story locks and hard locks (feedback 1.23, 1.39, 1.46)

> "make sure you can actually get to the next place without stuff from Emerald blocking you so you're not
> story locked, or you get transported to the next place without stuff blocking you" – playtester, round 1
>
> "once 6-7 is done make sure there's no story locks until the post game" · "do one last check to make sure
> there's no story locks or hard locks" – playtester, round 1 follow-ups 9 and 14

Round 1 moved, removed and replaced many vanilla events, and vanilla Emerald hides and moves its path
blockers with the flags and vars those events set. Two checkers walk the whole v2 story – the village to the
post-game – and look for what could stop the player. Decisions: D-213 – D-215 (the story-lock audit of Acts 1–5),
D-263 – D-265 (the whole game, the hard-lock check), D-265a (the Act 7 extension, the rivals' route fights, Lance;
lost multi battles and the village's way home).

```sh
python3 tools/hack/check_progression.py            # every leg + the warp check; exit 1 on a lock      (~45 s)
python3 tools/hack/check_progression.py --leg 4.16 # one leg, with its notes and guesses
python3 tools/hack/check_progression.py --markdown # the leg table below
python3 tools/hack/check_progression.py --state 4.16 --grep SLATEPORT   # simulated flags/vars at a leg
python3 tools/hack/check_hardlock.py               # the hard-lock check; exit 1 on a LOCK         (~2-5 min)
python3 tools/hack/check_hardlock.py -v            # with the notes (retries, whiteouts, by-design spots)
python3 tools/hack/check_hardlock.py --battles [--markdown]   # every round 1 battle and what a loss does
python3 tools/hack/emu/play.py tools/hack/emu/tests/progression.play -o DIR   # the D-213 fix, in the game
python3 tools/hack/emu/play.py tools/hack/emu/tests/hardlock.play -o DIR      # the engine facts the hard-lock check relies on
```

**Result on the head (da506630: Acts 1–7 with the revenge arc and the Act 7 extension, Lance, the post-game; Steven
as Champion):** 136 story legs and 9 side trips, 0 failing; 34 warp destinations open; hard-lock check 0 LOCK,
0 CHECK (105 notes, all by design or emulator-checked). No script had to change in this pass: the four failing legs
were the table's (Act 7 still in its pre-extension order), and one vanilla scene the table skipped (the Devon
scientist's PokéNav call) now has its leg. The one story lock found earlier (the Aqua Hideout, D-213) stays fixed.

## How the story-lock checker works

`tools/hack/check_progression.py` reads the real project data (compiled event scripts including the `.inc`
Poryscript writes, `map.json`, layouts, metatile behaviours, constants and enums through the C preprocessor) and
the story table `tools/hack/progression.json`. Details are in the script's docstring; in short:

- **Story table** – 136 legs in v2 story order (ids `1.xx` – `7.xx`, the post-game `P.xx`; the revenge arc's
  `6.R1` – `6.R7`, the rivals' route fights `2.06r`, `3.01r`, `4.09r`, `4.16r`, `5.05r`) plus 9 side trips. A leg
  names the scene(s) that happen first (their script labels; the checker finds the object, coord trigger, sign or
  OnFrame entry that starts each) and the badges/HMs the player has by then; then the player walks to where the
  next leg's first scene starts. Fields: `to` (a tile, a map or a label instead of the next scene), `via`
  (waypoints walked through first – entering a map runs its load scripts for real, e.g. leaving Birch's lab moves
  the National Dex state on), `then` (where a scene with a YES/NO, a menu, a boat or a ferry leaves the player;
  branches warping elsewhere give way, and a `then` the scene never warps to is reported), `expect`
  (flags/vars/items/`TRAINER_X` the scene must set), `pre` + `why` (what C code does first: the egg's step hook,
  the SS Tidal's crossing), `side`; table-wide `assume` (what a specialvar's C function returns:
  `HasAllHoennMons` FALSE), `puzzles` (gyms whose puzzle is C code: only getting in is checked) and `no_heal_ok`
  (maps where being shut in is the design, for the hard-lock check).
- **Flag/var simulator** – starts from the new game (`EventScript_ResetAllMapFlags` + the Draconid setup),
  then runs every scene statically: set/clear/var ops, `removeobject` (= the object's flag), items, trainer and
  multi battles, call/goto/conditionals/switch, `checktrainerflag` (Poryscript's `defeated()`); entering a map runs
  its OnTransition/OnLoad/OnResume and the first OnWarp entry due (objects it `addobject`s count as shown). A
  condition the state decides takes its branch; an unknown one (YES/NO, multichoice, a battle's outcome,
  `VAR_FACING`, a menu special's `VAR_RESULT`) takes both, keeps a value written on one side only (the player takes
  the path that moves the story on) and is listed as a guess (`-v`); a branch cut short in a loop or repeating a
  state already seen gives way to the other; a warp after a branch on the player's answer is only a "may warp"
  (Poryscript's `compare VAR_RESULT, X` + `goto_if_ne` counts as one), so the table says where with `then`. C
  effects it knows: the cable car's warp, the Hall of Fame's and the
  credits' way home to the bedroom (`GameClear` also sets `FLAG_SYS_GAME_CLEAR`). The player's scripted movement
  is followed (`applymovement` on the player, `getplayerxy`), so the walk after a scene starts where the scene
  left the player (the Elite Four's walk-in, the League guards). Each scene is checked: can it start (object
  shown, trigger var matching, OnFrame entry due), does it set what the table expects, does an OnFrame scene move
  its var on (else it would restart every frame).
- **Reachability** – a breadth-first search over tiles across maps: connections, warps as the engine takes
  them (doors walked into from below, arrow warps, step warps), dive/emerge (incl. `setdivewarp`), holes,
  Fly from outdoors to towns reached before. Each map is seen after its load scripts ran on the simulated
  state (`setmetatile`, `setmaplayoutindex`, `setobjectxyperm`, temp flags cleared). Blocked by collision,
  elevation, one-way ledges and directional tiles; objects whose flag is clear (unless talking to them makes
  them leave or step aside – an item ball, a Devon Scope Kecleon, the Space Center's stair guard, the League's door
  guards); coord triggers whose var matches and whose script walks the player back; water, waterfalls, dive spots,
  Strength boulders, Rock Smash rocks and Cut trees unless the **HM is in the bag and its badge is won**
  (`src/field_move.c`; no Pokémon needs to know the move); Acro Bike rails / bumpy slopes and Mach Bike mud
  slopes unless a bike is in the bag. A blocked leg is searched again with every obstacle passable at a cost,
  and the first obstacle on the cheapest path is reported with what clears it (the flag or var and every
  script that writes it). If a coord scene the player can reach clears the way, it is triggered – on the
  path it is part of the walk (Route 121's Aqua grunts), off the path it is a **detour** the story doesn't
  lead to, and counts as a lock.
- **Warps** – every `warp`/`warpsilent`/`warpwhitefade`/… destination in the round 1 scripts and every warp a
  table scene took: the tile is walkable and joins an exit of its map (no closed pocket). 34 checked.

## How the hard-lock checker works

`tools/hack/check_hardlock.py` (D-264) follows every path of the round 1 scripts on its own – the files in
`data/scripts/draconid/`, the new maps' `scripts.pory`, and every vanilla label block with an `@ Draconid Emerald`
line – from each place the game starts one (objects, coord triggers, signs, OnFrame and OnWarp tables, the
scripts C starts: the egg's hatch, Maxie's calls). It forks at every branch a path can't decide and remembers the
branches it took (a flag found set stays set; a `switch` on `VAR_FACING` with a case per direction has no fourth
way out). Scenes the story table plays start from the table's simulated state; the reachability is
check_progression's tile search, plus the table's rides (every scene with a `then`: Mr. Briney's boats, the cable
car, the ferries – the boatman who sails with the player counts as there) and every object whose script warps.

| Check | Looks for | Severity |
|---|---|---|
| lock | a `lock`/`lockall` written in round 1 code still in force when its script ends, with no battle in between | CHECK: the engine unlocks the player's controls whenever a script ends (`ScriptContext_RunScript`); only the other objects stay frozen until the map reloads, and back from a battle they are set up again unfrozen (both emulator-checked, `hardlock.play`) |
| wait | an explicit `waitstate` with nothing since the last one that resumes the script – a warp, a special marked `waitstate=1` in `data/specials.inc` (the macro adds its own), C code that calls `ScriptContext_Enable` or returns with `CB2_ReturnToFieldContinueScript*` (two calls deep); a movement script without `step_end` or with a non-movement command | LOCK: the player stays frozen |
| frame | an OnFrame entry with a path that neither changes its var nor warps | LOCK if no choice is on the path (it restarts every frame), NOTE if a YES/NO or a lost battle is (a forced retry) |
| coord | a coord trigger with a path that leaves its var, the player's tile and the map as they were | NOTE when the player can step off onto a tile without that trigger (stepping back on starts it again), LOCK when every tile off it is the same trigger or a wall |
| battle | every round 1 battle and what a loss does: goes on (`FLAG_DRACONID_NO_WHITEOUT`, an early-rival battle, the first battle, **every multi battle**: `BattleSetup_StartMultiBattle` ends in `CB2_EndSpecialTrainerBattle`, which goes back to the script whatever the outcome – `hardlock.play` section 4) – then is the flag cleared again? – or whites out. A loss that goes on is a path of its own: no trainer flags (set on a win only; a multi battle sets none, its script does), `GetBattleOutcome` gives `B_OUTCOME_LOST`, the early-rival battle `VAR_RESULT` TRUE | LOCK if a whiteout leaves the scene unable to start (its object hidden, its trigger's var moved on before the battle; temp state reset, `EventScript_WhiteOut` run) – unless someone on the map fights the same battle again (Lance, who stays in the village) –, or if the player can't walk back to it from the Pokémon Center they last used. The respawn can be any Pokémon Center the story passed in this act or the one before (the village house in Acts 1–2), with what that Center's load scripts wrote when the player passed it (Mr. Briney's spot, `Common_EventScript_UpdateBrineyLocation`); CHECK for scenes outside the table whose own writes disarm them |
| trap | every place a scene can warp the player to (every branch: a YES/NO, the ferry's menu), other than where the leg's walk starts: a heal location or the leg's next scene must be reachable with what the player has | LOCK; NOTE on `no_heal_ok` maps (the Elite Four, the Hall of Fame, the SS Tidal) |
| reentry | a story-scene path that gives control back before the scene is done (it writes less than another path of the same scene: a declined prompt, a lost battle; a won battle's own trainer flags don't count) must leave the scene startable after leaving and re-entering the map (temp vars and flags reset, load scripts run) or retryable by talking to someone there (whoever fights the battle the longer path fights: a declined challenge); a path that **sends the player elsewhere** instead (a lost village battle: `Draconid_EventScript_VillageLost` carries them home to (8, 6)) must leave the scene startable and its place reachable from where the warp lands, with the rides of the walk back after a whiteout; a temp var a script sets to the value a warp's destination waits for (lost in the warp) | LOCK / CHECK |

Save and reload need no check of their own: `CB2_ContinueSavedGame` keeps the temp vars and flags as saved and
restores the objects where they stood, so a reloaded game is the map as the player left it; leaving and
re-entering the map is the case that resets temp state, and the reentry check covers it.

The checker was tested by breaking five scripts on purpose (then restoring them): the homecoming OnFrame scene
without its `setvar VAR_DRACONID_FINALE_STATE` (frame LOCK), a `waitstate` added to the meteor alert (wait
LOCK), Brendan's Rustboro scene moving `VAR_BRENDAN_STATE` on before the battle (battle LOCK: a whiteout can't
restart it), the Lilycove ferry's Southern Island branch landing in the link Trade Center (trap LOCK), the egg
ceremony without its `releaseall` (lock CHECK). All five were reported, at the right file:line.

## What blocked, and what changed

| # | Leg | Found | Fix |
|---|---|---|---|
| 1 | 4.16 Magma Hideout → Aqua Hideout | **Detour.** Maxie's call after the promotion sends the player to Aqua's hideout in Lilycove, but vanilla keeps two grunts in its entrance (Aqua Hideout 1F (13, 11), (14, 11)) until the Slateport harbor scene (`SlateportCity_Harbor_EventScript_AquaEscapeScene`: Archie steals Stern's submarine, `setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_1/2_BLOCKING_ENTRANCE`), which vanilla set up in the Magma Hideout and nothing in the v2 story leads to. The checker: *"the way opens only after SlateportCity_Harbor_EventScript_AquaEscapeTrigger3 on SlateportCity_Harbor (8, 14), off the path"*. | D-213: Archie takes the submarine off-screen. `MagmaHideout_4F_EventScript_Maxie` no longer sets up the Slateport scenes (Stern and Gabby & Ty in the city, `VAR_SLATEPORT_CITY_STATE`/`VAR_SLATEPORT_HARBOR_STATE` 1); it calls `MagmaHideout_4F_EventScript_DraconidAquaTakesSubmarine` (`data/scripts/draconid/progression.pory`), which sets what the harbor scene left set: both states 2, Stern in the harbor (his vanilla "Why…" line), `FLAG_MET_TEAM_AQUA_HARBOR`, `FLAG_HIDE_LILYCOVE_MOTEL_SCOTT`, the two entrance grunts hidden. The Aqua Hideout's own scene still shows the submarine leave with Archie, and Nerine and Maxie's next call already speak of it. |
| 2 | 1.03 – 1.05 the opening | **Stale table** (not a game problem): the legs still named the egg ceremony in the Elder's house, the hatching rite and the Running Shoes as they were before the opening rework (D-230/D-231); 1.03 – 1.05 failed on the head. | D-263: the legs describe the opening as it is: the prophecy in the Elder's house, which warps to the shrine (1.03); the egg ceremony there, an OnFrame scene on `VAR_TEMP_1` that the shrine's OnTransition arms (1.04, expects the egg and `DRACONID_STATE_EGG_RECEIVED`); the hatch – `DraconidVillage_EventScript_EggHatch`, started by the C step hook `Draconid_ShouldHatchEgg` on the 5th step outdoors (`map` + `why`; the gatekeeper's triggers keep the player in the village until then) – and the old woman's Running Shoes (1.05). |
| 3 | 7.01 – 7.05 the finale | **Stale table** (not a game problem): the Act 7 extension (D-200 – D-209) put the Elder's call, the shrine seal, Regidrago and Wallace before the Trial of Three and the attack on the village after the summit; the old legs failed on da506630 (7.01: the Trial's OnFrame entry isn't the one due, the Elder's call is; 7.03: the summit no longer ends the game; 7.04: the wake-up waits for the village). | D-265a: Act 7 is 17 legs in the extension's order (7.01 – 7.17, below), the Elder's NO a side trip (7.04b). |
| 4 | 2.06r Brendan at Mr. Briney's cottage | **Table gap** (not a game problem): the trigger below the cottage door needs `VAR_ROUTE104_STATE` 1, which the vanilla Devon scientist's PokéNav scene sets – an OnFrame scene in Rustboro as the player comes out of Devon Corp. that the table didn't play (walks only note OnFrame scenes they pass). | D-265a: leg 2.06a plays it (`RustboroCity_EventScript_ScientistAddMatchCall`, expects `VAR_ROUTE104_STATE=1`). |

### Hard-lock findings (D-264, D-265)

**None that blocks:** 0 LOCK, 0 CHECK on the head; no script changed. What the check found in round 1's pass (54
battles, 63 notes on that head; the next section adds the Act 7 extension, the rivals and Lance – on da506630 the
check sees 86 battles and 105 notes, `check_hardlock.py -v`; the battle table below has every one). The Sootopolis
multi battle and the LEGENDS' TAG are multi battles: since D-265a a loss there goes on (they handle it themselves):

- **Every whiteout battle restarts.** 41 of the 54 round 1 battles white out on a loss (the gym leaders' reworked scripts,
  Nerine's fights 1–6, the rivals and Wally, Maxie and the Sootopolis multi battle, Matt, Archie, the post-game
  battles); none of them writes anything before the battle that hides its scene or disarms its trigger, and for
  every one in the story table the player can walk back from every Pokémon Center they may have used last – Mr.
  Briney's boats included (a whiteout moves him to where he was when that Center was entered). The Champion's
  room is the Elite Four's vanilla gauntlet: a loss resets them. `hardlock.play` loses to Brendan at Rustboro on
  purpose: the player wakes at home, Brendan and his trigger are still there, and the scene plays again.
- **Every lost battle that goes on cleans up.** The 13 battles a loss doesn't end (`FLAG_DRACONID_NO_WHITEOUT`:
  Aster on Draconid Pass, the Space Center tag battle, the Trial of Three, Zinnia, Rayquaza and Deoxys at the summit;
  the early-rival rule: May on Route 103, Aster at Meteor Falls, Brendan on Mt. Chimney and Jagged Pass, May in
  Lavaridge and Mossdeep; the first battle, Birch's rescue on Route 101) clear the flag again on every path.
  `hardlock.play` loses to Zinnia: healed, flag clear, state still the climb, Zinnia asks again, and re-entering the
  floor restarts the scene.
- **Every early way out can be tried again** (the reentry notes): a declined YES/NO or a lost battle in the Trial
  of Three, Zinnia, the Elder's lift ("Then make ready…": talking to the Elder asks again), May's and Brendan's
  post-game battles and their double, Aster at the shrine, Nerine by the pond, Deoxys, Wallace, Wes, Red, Blue and
  the LEGENDS' TAG, the Lilycove rivals, the Lavaridge traveller, the museum fee – each restarts on re-entry or by
  talking to someone there.
- **No OnFrame scene loops, no waitstate hangs, no movement script runs on.** Every OnFrame entry of round 1 moves
  its var on (or its gate temp var: the finale's `VAR_TEMP_7`) on every path; every explicit `waitstate` follows a
  warp, a self-waiting special or C that resumes (`Draconid_DoRayquazaFlightScene` returns through
  `CB2_ReturnToFieldContinueScriptPlayMapMusic`).
- **One coord note:** `Route119_EventScript_DraconidTabithaOrder` keeps its trigger armed (it tests its own flag and
  ends at once after the first time) – a no-op on re-entry, by design.
- **Traps:** none. The ferry menus' other branches (Southern Island, Navel Rock, Birth Island, Faraway Island) all
  have their boat back; the SS Tidal's crossing, the Elite Four and the Hall of Fame are shut-in by design
  (`no_heal_ok`).
- **The engine fact behind the lock check** (emulator, `hardlock.play` section 1): the Space Center raid ends in the
  vanilla `MossdeepCity_SpaceCenter_2F_EventScript_DefeatedMaxieTabitha`, whose `releaseall` is only under
  `BUGFIX` – yet the player walks off right away and no object is frozen (back from the multi battle the objects
  were set up again). A missing release is cosmetic at worst; the checker reports one only without a battle in
  between, as a CHECK.

Nothing to pass on to the other agents from this pass: no finding in their files.

### The Act 7 extension, the rivals' route fights, Lance (D-265a)

0 LOCK, 0 CHECK again, with the new legs in the table and two things the check didn't model before (a lost multi
battle and a loss that sends the player elsewhere). What it shows (the battle table below has every line):

- **Act 7 in its new order walks through** (7.01 – 7.17): the Elder's call at the foot of the Sky Pillar (its OnFrame
  entry `VAR_TEMP_7` 2 is the one due) and his dragon to the village (19, 6); the shrine seal scene (the shrine's
  OnTransition arms `VAR_TEMP_1` 2) and down through the opened wall; Regidrago (won, caught or fled moves the village
  state on); back up through the doorway the shrine's OnTransition sees the player at (10, 4) and arms the Elder's
  lift; Wallace (`TRAINER_WALLACE_SKY_PILLAR`); the Trial, Zinnia, the summit and its alarm (`VILLAGE_STATE_ALARM`,
  the landing at (19, 24)); the arrival, the three house doubles in the order Wally – May – Brendan (any order works:
  each house is its own trainer flag), Aster's double, the Primal multi (`ITEM_RED_ORB`, `ITEM_BLUE_ORB`), the
  goodbyes and the credits from the village (`FINALE_STATE_METEOR_DESTROYED`), the wake-up and the SS Ticket. The
  Elder's NO at the shrine leaves the way by the player's own wings open (7.04b).
- **A lost village battle sends the player home, and the fight waits.** All five (the three houses, Tabitha and
  Shelly with Aster, Maxie and Archie with Brendan or May) are multi battles, which never white out:
  `Draconid_EventScript_VillageLost` heals the party and warps to the house (8, 6); the house's grunts, the admins
  or Maxie and Archie are still there (no trainer flag, the village state as it was), talking to them starts the
  battle again, and the way back from the house is open. `hardlock.play` section 4 loses Wally's house with the
  whiteout flag off: the player is at (8, 6) – a whiteout would respawn them at (2, 7) or another Pokémon Center –,
  the grunts' flags are clear, the same double starts again and is won.
- **The revenge arc** (6.R1 – 6.R7): every battle whites out and restarts, the way back open from the Centers of
  Acts 5–6 (Lilycove, Mossdeep, Sootopolis, Ever Grande). **The Aqua gauntlet's whiteout restart**: each of its six
  battles leaves `VAR_TEMP_3` re-armed on re-entry (Shelly's flag is the only "done"), and the scene clears the five
  grunts' flags at its start, so the next try starts over at the first grunt (emulator: `magma_revenge.play` 4b).
  The grunt by the Ever Grande Pokémon Center is a sight trainer off the table's path (static check only).
- **Wallace at the Sky Pillar** (`FLAG_DRACONID_NO_WHITEOUT`): a loss heals, clears the flag, and talking to him or
  re-entering fights again. **Regidrago** whites out (D-202): it comes back (a temp flag) and the depths are reachable
  from every Center the story passed. **Groudon and Kyogre** (7x.01 – 7x.02): visible once the finale is over, a
  whiteout leads back to them.
- **Lance** (P.02b, D-261): P.01's walk out of the house after the SS Ticket is the first post-game visit and arms him
  (`FLAG_DRACONID_LANCE_ARMED`); the next arrival on the fly spot (8, 15) – out of the door or by Fly – plays his
  landing, the battle, Dratini and the Dragoninite. Declined, he waits in the village and asks again; arriving
  elsewhere, the scene waits for a later visit; a loss whites out and he stays – talking to him fights again – with
  the way back open. He and his Dragonite don't block the way across the square to the gate.
- **The rivals' route fights** (rivals2.pory): Brendan below Mr. Briney's cottage (2.06r), Wally at the cable car
  fence (3.01r) and on Route 120's south bridge (4.09r) are must-win – a whiteout leaves the trigger armed and the
  way back open; Brendan at the Magma Hideout door (4.16r) and May outside the Space Center (5.05r) are early-rival
  battles (a loss heals and goes on). May's Lavaridge battle stays part of 3.07.

## Checked and kept

Vanilla requirements the v2 order still meets (D-215; no change):

- **Norman's four badges** – `PetalburgCity_Gym_EventScript_Norman` battles at `VAR_PETALBURG_GYM_STATE` 6: the Wally
  tutorial (2) plus the four badges' `addvar`s; the checker expects the Balance Badge from the scene (4.02).
- **Route 112 cable car grunts** – hidden by the Meteor Falls scene (act3); **Mt. Chimney → Jagged Pass**, the
  Mega Ring trigger and the cable car back (side trip 3.03b) are open.
- **HM Strength for the Magma Hideout** (its 1F boulders) – vanilla too. The Rusturf Tunnel reunion hands it over
  once the rocks are smashed, and the only land route from Lavaridge back to Petalburg for Norman (no Surf yet)
  runs through that tunnel (legs 3.07–3.08; `pre` stands in for the C that counts the smashed rock).
- **Mr. Briney** after Peeko's rescue (2.07), both boat rides back (side trips 2.07b, 2.10b), the way back
  through Petalburg Woods from the outpost door (1.14b).
- **Kecleons** (Route 119/120, the Fortree Gym) go with the Devon Scope from Steven (4.08); **Route 121's Aqua
  grunts** leave when the player walks up to them (4.09).
- **The Jagged Pass guard** opens the hideout for Maxie's emblem (4.15); **the Space Center's stair guard**
  steps aside after the rank test (5.03).
- **Sootopolis** – in by diving (Route 126); after the turn Archie and Maxie must both be talked to before the
  Gym door unlocks (`FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE`, vanilla), then Wallace gives Waterfall and steps aside
  (5.12–5.14).
- **Acts 6–7** – Waterfall opens the way from Sootopolis over Route 128 and the Ever Grande waterfall to Victory Road
  (5.15's walk, with the revenge arc's ambushes 6.R1 – 6.R7 on the way); Wally's entrance battle (6.01); the League's door guards step aside for the badges
  (6.02); each Elite Four room shuts behind the player and opens ahead once its member is beaten (6.03 – 6.06, the
  walks start where the walk-in leaves the player); Steven, Brendan, Birch and May, then the Hall of Fame sends the
  player home to the bedroom (6.07 – 6.08); the homecoming and the meteor alert (6.09 – 6.10); the Elder's dragon
  lands the player at the Sky Pillar, and his NO leaves the way by Fly and Surf to Route 131 open (side trip
  6.10b); the Act 7 extension in its order: the Elder's call, the shrine and Regidrago, the lift back (7.01 – 7.04,
  side trip 7.04b), Wallace, the Trial of Three, Zinnia and the summit, each warping on to the next (7.05 – 7.08); the
  attack on the village (7.09 – 7.14); the credits from the village end in the bedroom, and the Elder brings the SS
  Ticket (7.15 – 7.17).
- **The post-game** (one order of many, from home): Nerine by the pond and Aster at the shrine (P.01 – P.02, both
  shown by the finale); Birch's National Dex scene in Littleroot and the lab, out and back in (P.03 – `via`), May,
  Brendan and their double (P.04 – P.06; `assume` HasAllHoennMons FALSE keeps the Johto starter scene out of the
  way); the SS Tidal from Slateport (the SS Ticket), Scott's invitation on board, the crossing (`pre`), Lilycove
  (P.07 – P.08); the ferry from Lilycove to the Battle Frontier (FLAG_MET_SCOTT_ON_SS_TIDAL), Blue, Red, Wes and
  the LEGENDS' TAG, the ferry back (P.09 – P.14); Deoxys on the summit (P.15); the Elite Four again (the Hall of
  Fame reset them) and Steven's rematch, the Hall of Fame again (P.16 – P.20); Wallace by the Cave of Origin and
  Steven's Meteor Falls chat (P.21 – P.22); side trips: Lance in the village (P.02b), Groudon in the Magma Hideout and
  Kyogre in the Seafloor Cavern (7x.01 – 7x.02).
- **No OnFrame loops** in any scene the table plays or the walks pass; all 34 warp destinations are open.

## In the emulator

- `tools/hack/emu/tests/progression.play` (from `rustboro_done.ss`): Maxie's promotion in the Magma Hideout, then
  the flags (`VAR_SLATEPORT_*` 2, the entrance grunts hidden, Stern in the harbor), a walk from the Aqua Hideout
  landing (13, 12) north through the grunts' tile to (13, 9), and Stern's line in the Slateport harbor.
- `tools/hack/emu/tests/hardlock.play` (after act7.play; `woods_done.ss`, `act5_space_center.ss`, `act7_3f.ss`):
  (1) right after the Space Center raid – a script that ended with `lockall` in force – the player walks;
  (2) a lost battle with Brendan at Rustboro whites out, the player wakes at home, Brendan's trigger and object are
  still there and the scene plays again; (3) a lost battle with Zinnia goes on: the party is healed, the
  no-whiteout flag is clear, the finale state stays at the climb, Zinnia asks again (NO), and re-entering the floor
  restarts the scene, which is then won and leads to the summit; (4) from `rustboro_done.ss` with the village under
  attack set by hand (as `act7x.play`), Wally's house double lost with the whiteout flag off: home at (8, 6), not a
  respawn, the grunts' flags clear, `VILLAGE_STATE_ATTACK`; out of the door, the same double again, won.
  Screenshots `hl_*` looked at.
- The other branches' flow tests back the D-265a modelling on the same ROM: `act7x.play` (a village loss, the fight
  waits; Regidrago and Wallace lost first), `magma_revenge.play` (the gauntlet lost mid-way starts over at the first
  grunt), `lance.play` (armed, then the landing).
- The regression chain opening → route103 → woods → rustboro → act2 → act3 → act4 → act5 → act6 → act7 →
  hardlock → act7x → magma_revenge → lance → rivals2 → postgame_home was regenerated on this ROM before any run.

## Not modelled

What C code does inside specials (a special's `VAR_RESULT` is a fork; the egg's step hook and the SS Tidal's
crossing are given by the table), the party (every battle can be won or lost; "you need two Pokémon" is a fork),
gym puzzles (the table's `puzzles`: getting in is enough), sea currents, the Sky Pillar's cracked floors (walkable,
as with the Mach Bike), which Pokémon Centers the player really used (any one the story passed in this act or the
one before), wild battles (a whiteout goes to the same Center), random and timed events, and scripts that only
other data points to (Match Call texts: their C hooks are followed). Battles of scenes outside the story table
(side trainers, the Ever Grande Center grunt, rematches) get the static part of the battle check (their own writes
don't disarm them) but no walk back. OnFrame scenes a walk passes are noted, not played: one the story depends on
needs its own leg (2.06a).

## Extending

The revenge arc (6.R1 – 6.R7), the Act 7 extension (7.01 – 7.17, 7x.01 – 7x.02), Lance (P.02b) and the rivals' route
fights (`r` legs) are in. Still to add when they merge (D-265a): the more Aster/Nerine battles (Granite Cave B1F in
Act 2 – on the only way to Steven, so a leg before 2.09; Route 121 in Act 4, before 4.12; the village after Juan's
badge – side trips after 5.15; the post-game double by the pond – a post-game side trip) and the Z-Power gifts
(`expect` the ring on 7.04, Prof. Oak's post-game scene in Birch's lab as a `P` leg).

1. Put the new scenes into `tools/hack/progression.json` where they happen in the story, as legs with their own
   ids (`2.08r`, `4.11r`, `P.02c`, …; a `b`/`c` suffix for side trips). A leg: the scene
   label (`at`/`map`/`talk` if the label is used in several places or started by C), `expect` for the flags, vars,
   items and `TRAINER_X` the next leg needs, `then` where a warp or a choice leaves the player, `via` for a walk
   that must pass a map first, `pre` + `why` for what C does, `from` for a side trip that starts elsewhere (Lance:
   the fly spot). If the scene moves an existing scene (e.g. the finale's start), change that leg's scene label
   instead of adding a leg. An OnFrame scene a walk passes is not played: give it a leg if the story needs it.
2. Run `check_progression.py` (0 failing) and `check_hardlock.py` (0 LOCK): new battles, OnFrame scenes, retries and
   warps are picked up from the scripts by themselves; a by-design shut-in map goes under `no_heal_ok`.
3. Paste `check_progression.py --markdown` and `check_hardlock.py --battles --markdown` below.

## The legs (Act 1 to the post-game)

Generated by `python3 tools/hack/check_progression.py --markdown`. "Walk" is from where the leg's scenes leave the
player to where the next scene starts.

| Leg | What happens (the scenes, then the walk) | Badges / HMs | Walk | Result |
|---|---|---|---|---|
| 1.01 | Bedroom: the night prologue, Aster at the door<br>`DraconidVillage_PlayersHouse_2F_EventScript_WakeUp` | 0 / – | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_2F next to (5, 1) | ok, 4 steps via DraconidVillage_PlayersHouse_2F |
| 1.02 | Set the wall clock, go to the Elder<br>`DraconidVillage_PlayersHouse_2F_EventScript_WallClock` | 0 / – | DraconidVillage_PlayersHouse_2F (5, 2) → DraconidVillage_EldersHouse (entering) | ok, 32 steps via DraconidVillage_PlayersHouse_2F, DraconidVillage_PlayersHouse_1F, DraconidVillage, DraconidVillage_EldersHouse |
| 1.03 | The prophecy in the Elder's house; the Elder takes the player up to the shrine<br>`DraconidVillage_EldersHouse_EventScript_Ceremony` | 0 / – | DraconidVillage_Shrine (10, 18) → DraconidVillage_Shrine (entering) | ok, 0 steps via DraconidVillage_Shrine |
| 1.04 | Egg ceremony in the shrine; out under the open sky<br>`DraconidVillage_Shrine_EventScript_EggCeremony` | 0 / – | DraconidVillage_Shrine (10, 9) → DraconidVillage (entering) | ok, 11 steps via DraconidVillage_Shrine, DraconidVillage |
| 1.05 | The egg hatches after 5 steps outdoors, the Running Shoes; down to Draconid Pass<br>`DraconidVillage_EventScript_EggHatch`<br>`DraconidVillage_EventScript_RunningShoes` | 0 / – | DraconidVillage (19, 5) → DraconidPass (10, 18) (11, 18) (12, 18) … | ok, 43 steps via DraconidVillage, DraconidPass |
| 1.06 | Aster's tutorial battle, on to Route 101<br>`DraconidPass_EventScript_AsterBattle` | 0 / – | DraconidPass (11, 18) → Route101 (0, 4) | ok, 25 steps via DraconidPass, Route101 |
| 1.07 | Birch's rescue, the lab<br>`Route101_EventScript_DraconidRescueTop` | 0 / – | LittlerootTown_ProfessorBirchsLab (6, 5) → LittlerootTown_ProfessorBirchsLab (entering) | ok, 0 steps via LittlerootTown_ProfessorBirchsLab |
| 1.08 | Lab welcome (Pokédex), to May on Route 103<br>`LittlerootTown_ProfessorBirchsLab_EventScript_DraconidWelcome` | 0 / – | LittlerootTown_ProfessorBirchsLab (6, 5) → Route103 next to (10, 3) | ok, 121 steps via LittlerootTown_ProfessorBirchsLab, LittlerootTown, Route101, OldaleTown, Route103 |
| 1.09 | May on Route 103, to Norman in Petalburg<br>`Route103_EventScript_Rival` | 0 / – | Route103 (9, 3) → PetalburgCity_Gym (entering) | ok, 125 steps via Route103, OldaleTown, Route102, PetalburgCity, PetalburgCity_Gym |
| 1.10 | Norman sends the player with Wally<br>`PetalburgCity_Gym_EventScript_Norman` | 0 / – | PetalburgCity (15, 8) → PetalburgCity (entering) | ok, 0 steps via PetalburgCity |
| 1.11 | Wally catches Ralts<br>`PetalburgCity_EventScript_WallyTutorial` | 0 / – | PetalburgCity_Gym (4, 108) → PetalburgCity_Gym (entering) | ok, 0 steps via PetalburgCity_Gym |
| 1.12 | Back in the gym, to Petalburg Woods<br>`PetalburgCity_Gym_EventScript_ReturnFromWallyTutorial` | 0 / – | PetalburgCity_Gym (4, 111) → PetalburgWoods (26, 23) | ok, 114 steps via PetalburgCity_Gym, PetalburgCity, Route104, PetalburgWoods |
| 1.13 | Nerine robs the researcher, Courtney recruits the player<br>`PetalburgWoods_EventScript_DevonResearcherLeft` | 0 / – | PetalburgWoods_MagmaOutpost (4, 6) → PetalburgWoods_MagmaOutpost (entering) | ok, 0 steps via PetalburgWoods_MagmaOutpost |
| 1.14 | Outpost cabin: the uniform, out to Route 104 and Rustboro<br>`PetalburgWoods_MagmaOutpost_EventScript_Uniform` | 0 / – | PetalburgWoods_MagmaOutpost (4, 6) → RustboroCity (12, 53) | ok, 77 steps via PetalburgWoods_MagmaOutpost, Route104, RustboroCity |
| 1.14b | Way back: from the outpost door through Petalburg Woods to Petalburg *(side trip)*<br>– | 0 / – | Route104 (10, 30) → PetalburgCity (20, 17) | ok, 108 steps via Route104, PetalburgWoods, Route104, PetalburgCity |
| 1.15 | Brendan at Rustboro's south edge, to Roxanne<br>`RustboroCity_EventScript_RivalTrigger0` | 0 / – | RustboroCity (12, 53) → RustboroCity_Gym next to (5, 2) | ok, 73 steps via RustboroCity, RustboroCity_Gym |
| 1.16 | Stone Badge, out of the gym<br>`RustboroCity_Gym_EventScript_Roxanne` | 1 / – | RustboroCity_Gym (4, 2) → RustboroCity (entering) | ok, 25 steps via RustboroCity_Gym, RustboroCity |
| 1.17 | Tabitha's order, Birch's second starter<br>`RustboroCity_EventScript_DraconidSecondStarter` | 1 / – | RustboroCity (27, 19) → RustboroCity (23, 20) | ok, 5 steps via RustboroCity |
| 2.01 | Nerine steals the Devon Goods, Tabitha's order<br>`RustboroCity_EventScript_StolenGoodsTrigger0` | 1 / – | RustboroCity (23, 20) → RustboroCity (30, 9) | ok, 20 steps via RustboroCity |
| 2.02 | The Devon employee asks for help, to Route 116<br>`RustboroCity_EventScript_HelpGetGoodsTrigger0` | 1 / – | RustboroCity (30, 9) → Route116 (47, 9) | ok, 71 steps via RustboroCity, Route116 |
| 2.03 | Mr. Briney's Peeko, into Rusturf Tunnel<br>`Route116_EventScript_BrineyTrigger` | 1 / – | Route116 (47, 9) → RusturfTunnel next to (13, 5) | ok, 15 steps via Route116, RusturfTunnel |
| 2.04 | Nerine fight 2, the goods choice, back to Rustboro<br>`RusturfTunnel_EventScript_Grunt` | 1 / – | RusturfTunnel (12, 5) → RustboroCity (30, 9) | ok, 83 steps via RusturfTunnel, Route116, RustboroCity |
| 2.05 | The employee takes the goods back, to Mr. Stone<br>`RustboroCity_EventScript_ReturnGoodsTrigger0` | 1 / – | RustboroCity_DevonCorp_3F (2, 2) → RustboroCity_DevonCorp_3F (entering) | ok, 0 steps via RustboroCity_DevonCorp_3F |
| 2.06 | Mr. Stone: PokéNav, Exp. Share, the letter; out of Devon Corp.<br>`RustboroCity_DevonCorp_3F_EventScript_MeetPresident` | 1 / – | RustboroCity_DevonCorp_3F (14, 5) → RustboroCity (entering) | ok, 48 steps via RustboroCity_DevonCorp_3F, RustboroCity_DevonCorp_2F, RustboroCity_DevonCorp_1F, RustboroCity |
| 2.06a | Out of Devon Corp.: the scientist's PokéNav match call (it sends Brendan to Mr. Briney's cottage, D-234); to Route 104<br>`RustboroCity_EventScript_ScientistAddMatchCall` | 1 / – | RustboroCity (12, 16) → Route104 (17, 51) | ok, 176 steps via RustboroCity, Route104, PetalburgWoods, Route104 |
| 2.06r | Brendan out of Mr. Briney's cottage (Route 104, D-234); into the cottage<br>`Route104_EventScript_RivalTrigger` | 1 / – | Route104 (17, 52) → Route104_MrBrineysHouse next to (9, 3) | ok, 11 steps via Route104, Route104_MrBrineysHouse |
| 2.07 | Mr. Briney sails to Dewford (Maxie's first call), to Brawly<br>`Route104_MrBrineysHouse_EventScript_Briney`<br>`Route104_EventScript_StartSailToDewford` | 1 / – | DewfordTown (11, 9) → DewfordTown_Gym next to (4, 3) | ok, 57 steps via DewfordTown, DewfordTown_Gym |
| 2.07b | Way back from Dewford before the letter: Mr. Briney sails to Petalburg *(side trip)*<br>`DewfordTown_EventScript_Briney` | 1 / – | Route104_MrBrineysHouse (5, 4) → PetalburgCity (20, 17) | ok, 65 steps via Route104_MrBrineysHouse, Route104, PetalburgCity |
| 2.08 | Knuckle Badge, to Steven in Granite Cave<br>`DewfordTown_Gym_EventScript_Brawly` | 2 / – | DewfordTown_Gym (4, 4) → GraniteCave_StevensRoom next to (7, 8) | ok, 270 steps via DewfordTown_Gym, DewfordTown, Route106, GraniteCave_1F, GraniteCave_B1F, GraniteCave_B2F, GraniteCave_B1F, GraniteCave_1F, GraniteCave_StevensRoom |
| 2.09 | Steven gets the letter, back to Mr. Briney<br>`GraniteCave_StevensRoom_EventScript_Steven` | 2 / – | GraniteCave_StevensRoom (7, 7) → DewfordTown next to (12, 9) | ok, 82 steps via GraniteCave_StevensRoom, GraniteCave_1F, Route106, DewfordTown |
| 2.10 | Sail to Slateport, to the shipyard<br>`DewfordTown_EventScript_Briney` | 2 / – | Route109 (21, 23) → SlateportCity_SternsShipyard_1F next to (5, 5) | ok, 68 steps via Route109, SlateportCity, SlateportCity_SternsShipyard_1F |
| 2.10b | Way back from Slateport before Surf: Mr. Briney sails to Dewford *(side trip)*<br>`Route109_EventScript_MrBriney` | 2 / – | DewfordTown (11, 9) → DewfordTown_Gym (entering) | ok, 19 steps via DewfordTown, DewfordTown_Gym |
| 2.11 | Dock: Stern is at the museum<br>`SlateportCity_SternsShipyard_1F_EventScript_Dock` | 2 / – | SlateportCity_SternsShipyard_1F (4, 5) → SlateportCity_OceanicMuseum_1F (9, 7) | ok, 45 steps via SlateportCity_SternsShipyard_1F, SlateportCity, SlateportCity_OceanicMuseum_1F |
| 2.12 | Museum fee, Tabitha's order, to Stern on 2F<br>`SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft` | 2 / – | SlateportCity_OceanicMuseum_1F (9, 7) → SlateportCity_OceanicMuseum_2F next to (13, 6) | ok, 21 steps via SlateportCity_OceanicMuseum_1F, SlateportCity_OceanicMuseum_2F |
| 2.13 | Aqua's raid (Nerine fight 2), Stern gets the parts; to Route 110<br>`SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | 2 / – | SlateportCity_OceanicMuseum_2F (12, 6) → Route110 (33, 56) | ok, 140 steps via SlateportCity_OceanicMuseum_2F, SlateportCity_OceanicMuseum_1F, SlateportCity, Route110 |
| 2.14 | May on Route 110 (PokéNav), to Mauville<br>`Route110_EventScript_RivalTrigger1` | 2 / – | Route110 (33, 56) → MauvilleCity next to (8, 6) | ok, 136 steps via Route110, MauvilleCity |
| 2.15 | Wally in Mauville, to Wattson<br>`MauvilleCity_EventScript_Wally` | 2 / – | MauvilleCity (8, 7) → MauvilleCity_Gym (entering) | ok, 2 steps via MauvilleCity, MauvilleCity_Gym |
| 2.16 | Dynamo Badge, to the Rock Smash house<br>`MauvilleCity_Gym_EventScript_Wattson` | 3 / – | MauvilleCity_Gym (4, 20) → MauvilleCity_House1 next to (4, 4) | ok, 39 steps via MauvilleCity_Gym, MauvilleCity, MauvilleCity_House1 |
| 2.17 | HM Rock Smash, to Rydel's bikes<br>`MauvilleCity_House1_EventScript_RockSmashDude` | 3 / Rock Smash | MauvilleCity_House1 (3, 4) → MauvilleCity_BikeShop next to (2, 5) | ok, 25 steps via MauvilleCity_House1, MauvilleCity, MauvilleCity_BikeShop |
| 2.18 | A bike from Rydel; north over Route 111, Fiery Path, Fallarbor to Meteor Falls<br>`MauvilleCity_BikeShop_EventScript_Rydel` | 3 / Rock Smash | MauvilleCity_BikeShop (3, 5) → MeteorFalls_1F_1R (14, 18) | ok, 587 steps via MauvilleCity_BikeShop, MauvilleCity, Route111, Route112, FieryPath, Route112, Route111, Route113, FallarborTown, Route114, MeteorFalls_1F_1R |
| 3.01 | Meteor Falls: Maxie, the stand-off with Aqua, Aster; to the cable car<br>`MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene` | 3 / Rock Smash | MeteorFalls_1F_1R (14, 18) → Route112 (26, 30) (27, 30) | ok, 433 steps via MeteorFalls_1F_1R, Route114, FallarborTown, Route113, Route111, Route112, FieryPath, Route112 |
| 3.01r | Wally at the cable car station's fence (Route 112, D-234); to the attendant<br>`Route112_EventScript_DraconidWally` | 3 / Rock Smash | Route112 (26, 30) → Route112_CableCarStation next to (6, 6) | ok, 10 steps via Route112, Route112_CableCarStation |
| 3.02 | Cable car up Mt. Chimney, to Maxie<br>`Route112_CableCarStation_EventScript_Attendant` | 3 / Rock Smash | MtChimney_CableCarStation (6, 4) → MtChimney next to (13, 6) | ok, 79 steps via MtChimney_CableCarStation, MtChimney |
| 3.03 | Mt. Chimney: Tabitha, Nerine fight 3, Brendan, the sabotage; down Jagged Pass<br>`MtChimney_EventScript_Maxie` | 3 / Rock Smash | MtChimney (12, 6) → JaggedPass (13, 8) (14, 8) | ok, 72 steps via MtChimney, JaggedPass |
| 3.03b | Way back from Mt. Chimney by cable car *(side trip)*<br>`MtChimney_CableCarStation_EventScript_Attendant` | 3 / Rock Smash | Route112_CableCarStation (6, 4) → Route112 (28, 29) | ok, 10 steps via Route112_CableCarStation, Route112 |
| 3.04 | Aster brings the Mega Ring, to the traveller in Lavaridge<br>`JaggedPass_EventScript_DraconidAster` | 3 / Rock Smash | JaggedPass (14, 8) → LavaridgeTown next to (17, 8) | ok, 40 steps via JaggedPass, Route112, LavaridgeTown |
| 3.05 | The Mega Stone, to Flannery<br>`LavaridgeTown_EventScript_DraconidTraveller` | 3 / Rock Smash | LavaridgeTown (18, 8) → LavaridgeTown_Gym_1F next to (13, 9) | ok, 99 steps via LavaridgeTown, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F, LavaridgeTown_Gym_B1F, LavaridgeTown_Gym_1F |
| 3.06 | Heat Badge, out of the gym<br>`LavaridgeTown_Gym_1F_EventScript_Flannery` | 4 / Rock Smash | LavaridgeTown_Gym_1F (12, 9) → LavaridgeTown (entering) | ok, 10 steps via LavaridgeTown_Gym_1F, LavaridgeTown |
| 3.07 | May's Go-Goggles; back towards Petalburg through Rusturf Tunnel<br>`LavaridgeTown_EventScript_RivalGiveGoGoggles` | 4 / Rock Smash | LavaridgeTown (5, 15) → RusturfTunnel (23, 4) | ok, 274 steps via LavaridgeTown, Route112, Route111, MauvilleCity, Route117, VerdanturfTown, RusturfTunnel |
| 3.08 | Rusturf Tunnel opened with Rock Smash: HM Strength; on to Petalburg<br>`RusturfTunnel_EventScript_ClearTunnelScene` | 4 / Rock Smash, Strength | RusturfTunnel (23, 4) → PetalburgCity (15, 9) | ok, 315 steps via RusturfTunnel, Route116, RustboroCity, Route104, PetalburgWoods, Route104, PetalburgCity |
| 4.01 | Wally at the Petalburg Gym door, to Norman<br>`PetalburgCity_EventScript_DraconidWallyTrigger` | 4 / Rock Smash, Strength | PetalburgCity (15, 9) → PetalburgCity_Gym (entering) | ok, 1 steps via PetalburgCity, PetalburgCity_Gym |
| 4.02 | Balance Badge (May watches), out to Wally's father<br>`PetalburgCity_Gym_EventScript_Norman` | 5 / Rock Smash, Strength | PetalburgCity (15, 8) → PetalburgCity (entering) | ok, 0 steps via PetalburgCity |
| 4.03 | Wally's father walks the player home<br>`PetalburgCity_EventScript_WalkToWallyHouse` | 5 / Rock Smash, Strength | PetalburgCity_WallysHouse (2, 4) → PetalburgCity_WallysHouse (entering) | ok, 0 steps via PetalburgCity_WallysHouse |
| 4.04 | HM Surf, over Route 118 to Tabitha at the Weather Institute<br>`PetalburgCity_WallysHouse_EventScript_GiveHMSurf` | 5 / Rock Smash, Strength, Surf | PetalburgCity_WallysHouse (2, 4) → Route119 (6, 33) | ok, 607 steps via PetalburgCity_WallysHouse, PetalburgCity, Route102, OldaleTown, Route103, Route110, MauvilleCity, Route118, Route119 |
| 4.05 | Tabitha's order, up to Shelly<br>`Route119_EventScript_DraconidTabithaOrder` | 5 / Rock Smash, Strength, Surf | Route119 (6, 33) → Route119_WeatherInstitute_2F next to (4, 6) | ok, 53 steps via Route119, Route119_WeatherInstitute_1F, Route119_WeatherInstitute_2F |
| 4.06 | Aqua leaves the Institute, May covers for the player, Tabitha's HM Fly; to Brendan<br>`Route119_WeatherInstitute_2F_EventScript_Shelly` | 5 / Rock Smash, Strength, Surf, Fly | Route119_WeatherInstitute_2F (5, 6) → Route119 (25, 31) | ok, 68 steps via Route119_WeatherInstitute_2F, Route119_WeatherInstitute_1F, Route119 |
| 4.07 | Brendan on Route 119 (a battle), to Fortree and Steven<br>`Route119_EventScript_RivalTrigger1` | 5 / Rock Smash, Strength, Surf, Fly | Route119 (25, 31) → Route120 next to (13, 15) | ok, 135 steps via Route119, FortreeCity, Route120 |
| 4.08 | Steven's Devon Scope, back to the Fortree Gym<br>`Route120_EventScript_Steven` | 5 / Rock Smash, Strength, Surf, Fly | Route120 (14, 15) → FortreeCity_Gym next to (15, 2) | ok, 115 steps via Route120, FortreeCity, FortreeCity_Gym |
| 4.09 | Feather Badge, over Route 121 to Lilycove<br>`FortreeCity_Gym_EventScript_Winona` | 6 / Rock Smash, Strength, Surf, Fly | FortreeCity_Gym (14, 2) → Route120 (34, 67) (34, 68) | ok, 190 steps via FortreeCity_Gym, FortreeCity, Route120 |
| 4.09r | Wally on the south bridge (Route 120, D-234); on to Lilycove<br>`Route120_EventScript_DraconidWally` | 6 / Rock Smash, Strength, Surf, Fly | Route120 (34, 67) → LilycoveCity next to (27, 7) | ok, 198 steps via Route120, Route121, LilycoveCity |
| 4.10 | Brendan and May in Lilycove (double), to Wally<br>`LilycoveCity_EventScript_Rival` | 6 / Rock Smash, Strength, Surf, Fly | LilycoveCity (28, 7) → LilycoveCity next to (26, 16) | ok, 3 steps via LilycoveCity |
| 4.11 | Wally's Mega Gallade, over Route 122 to the Mt. Pyre summit<br>`LilycoveCity_EventScript_DraconidWally` | 6 / Rock Smash, Strength, Surf, Fly | LilycoveCity (25, 16) → MtPyre_Summit (entering) | ok, 270 steps via LilycoveCity, Route121, Route122, MtPyre_1F, MtPyre_Exterior, MtPyre_Summit |
| 4.12 | Maxie's order and the Magma Emblem, down to Nerine<br>`MtPyre_Summit_EventScript_DraconidMaxieOrders` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (23, 30) → MtPyre_Summit (22, 10) (23, 10) (24, 10) | ok, 20 steps via MtPyre_Summit |
| 4.13 | Nerine fight 4, up to Archie<br>`MtPyre_Summit_EventScript_DraconidNerine` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (23, 10) → MtPyre_Summit (22, 7) | ok, 4 steps via MtPyre_Summit |
| 4.14 | Archie takes the Red Orb; to the Jagged Pass guard<br>`MtPyre_Summit_EventScript_TeamAquaTrigger0` | 6 / Rock Smash, Strength, Surf, Fly | MtPyre_Summit (22, 7) → JaggedPass next to (16, 19) | ok, 68 steps via MtPyre_Summit, Fly to LavaridgeTown, Route112, JaggedPass |
| 4.15 | The guard opens the hideout, up to Maxie<br>`JaggedPass_EventScript_MagmaHideoutGuard` | 6 / Rock Smash, Strength, Surf, Fly | JaggedPass (17, 19) → MagmaHideout_4F next to (16, 21) | ok, 316 steps via JaggedPass, MagmaHideout_1F, MagmaHideout_2F_1R, MagmaHideout_3F_1R, MagmaHideout_4F |
| 4.16 | Maxie's promotion, Groudon wakes and escapes; to the Aqua Hideout (Maxie's call)<br>`MagmaHideout_4F_EventScript_Maxie` | 6 / Rock Smash, Strength, Surf, Fly | MagmaHideout_4F (15, 21) → JaggedPass (entering) | ok, 120 steps via MagmaHideout_4F, MagmaHideout_3F_3R, MagmaHideout_2F_3R, MagmaHideout_1F, JaggedPass |
| 4.16r | Brendan as the player comes out of the Magma Hideout (Jagged Pass, D-235); to the Aqua Hideout<br>`JaggedPass_EventScript_DraconidBrendan` | 6 / Rock Smash, Strength, Surf, Fly | JaggedPass (16, 18) → AquaHideout_B2F next to (23, 19) | ok, 234 steps via JaggedPass, Fly to LilycoveCity, AquaHideout_1F, AquaHideout_B1F, AquaHideout_B2F, AquaHideout_B1F, AquaHideout_B2F |
| 5.01 | Aqua Hideout: Nerine fight 5 and Matt; over Route 124 to Mossdeep<br>`AquaHideout_B2F_EventScript_Matt` | 6 / Rock Smash, Strength, Surf, Fly | AquaHideout_B2F (24, 19) → MossdeepCity_Gym (entering) | ok, 250 steps via AquaHideout_B2F, AquaHideout_B1F, AquaHideout_1F, LilycoveCity, Route124, MossdeepCity, MossdeepCity_Gym |
| 5.02 | Mind Badge, to Tabitha's raid<br>`MossdeepCity_Gym_EventScript_TateAndLiza` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_Gym (6, 35) → MossdeepCity (40, 25) (40, 26) (41, 22) … | ok, 20 steps via MossdeepCity_Gym, MossdeepCity |
| 5.03 | Tabitha's raid order, into the Space Center<br>`MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity (41, 22) → MossdeepCity_SpaceCenter_2F (entering) | ok, 59 steps via MossdeepCity, MossdeepCity_SpaceCenter_1F, MossdeepCity_SpaceCenter_2F |
| 5.04 | Space Center 2F: the rank tests, to Steven and Brendan<br>`MossdeepCity_SpaceCenter_2F_EventScript_ThreeMagmaGrunts` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_SpaceCenter_2F (13, 1) → MossdeepCity_SpaceCenter_2F (7, 5) (7, 6) (7, 7) … | ok, 12 steps via MossdeepCity_SpaceCenter_2F |
| 5.05 | The tag battle, the sealed tanks; to Steven's house<br>`MossdeepCity_SpaceCenter_2F_EventScript_DraconidRaid` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity_SpaceCenter_2F (3, 8) → MossdeepCity (entering) | ok, 32 steps via MossdeepCity_SpaceCenter_2F, MossdeepCity_SpaceCenter_1F, MossdeepCity |
| 5.05r | May as the player comes out of the Space Center (Mossdeep, D-235); to Steven's house<br>`MossdeepCity_EventScript_DraconidMay` | 7 / Rock Smash, Strength, Surf, Fly | MossdeepCity (64, 15) → MossdeepCity_StevensHouse (entering) | ok, 17 steps via MossdeepCity, MossdeepCity_StevensHouse |
| 5.06 | HM Dive, down to the Seafloor Cavern<br>`MossdeepCity_StevensHouse_EventScript_StevenGivesDive` | 7 / Rock Smash, Strength, Surf, Fly, Dive | MossdeepCity_StevensHouse (3, 7) → SeafloorCavern_Room9 (entering) | ok, 261 steps via MossdeepCity_StevensHouse, MossdeepCity, Route127, Route128, Underwater_Route128, Underwater_SeafloorCavern, SeafloorCavern_Entrance, SeafloorCavern_Room1, SeafloorCavern_Room2, SeafloorCavern_Room7, SeafloorCavern_Room3, SeafloorCavern_Room8, SeafloorCavern_Room9 |
| 5.07 | Nerine's reveal (fight 6), to Archie<br>`SeafloorCavern_Room9_EventScript_DraconidNerineReveal` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SeafloorCavern_Room9 (5, 4) → SeafloorCavern_Room9 (17, 42) | ok, 62 steps via SeafloorCavern_Room9 |
| 5.08 | Kyogre wakes, back to Route 128<br>`SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre` | 7 / Rock Smash, Strength, Surf, Fly, Dive | Route128 (38, 22) → Route128 (entering) | ok, 0 steps via Route128 |
| 5.09 | Archie and Maxie on Route 128, dive to Sootopolis<br>`Route128_EventScript_KyogreAwakenedScene` | 7 / Rock Smash, Strength, Surf, Fly, Dive | Route128 (38, 22) → SootopolisCity (entering) | ok, 149 steps via Route128, Route127, Route126, Underwater_Route126, Underwater_SootopolisCity, SootopolisCity |
| 5.10 | Groudon and Kyogre clash, to Maxie on the Gym island<br>`SootopolisCity_EventScript_StartLegendariesScene` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (29, 53) → SootopolisCity next to (29, 33) | ok, 25 steps via SootopolisCity |
| 5.11 | The turn, Maxie, the multi battle, Rayquaza, the Elder's call, the rivals; to Archie<br>`SootopolisCity_EventScript_Maxie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (31, 34) → SootopolisCity next to (34, 35) | ok, 5 steps via SootopolisCity |
| 5.12 | Archie admits his failure, to Maxie<br>`SootopolisCity_EventScript_Archie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (34, 36) → SootopolisCity next to (33, 35) | ok, 1 steps via SootopolisCity |
| 5.13 | Maxie admits his, both leave (the Gym door opens); to Wallace<br>`SootopolisCity_EventScript_Maxie` | 7 / Rock Smash, Strength, Surf, Fly, Dive | SootopolisCity (31, 34) → SootopolisCity next to (31, 33) | ok, 0 steps via SootopolisCity |
| 5.14 | HM Waterfall, Wallace steps aside; to Juan<br>`SootopolisCity_EventScript_Wallace` | 7 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity (31, 34) → SootopolisCity_Gym_1F (entering) | ok, 2 steps via SootopolisCity, SootopolisCity_Gym_1F |
| 5.15 | Rain Badge (end of Act 5)<br>`SootopolisCity_Gym_1F_EventScript_Juan` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity_Gym_1F (8, 25) → SootopolisCity (30, 33) (31, 34) (32, 33) | ok, 3 steps via SootopolisCity_Gym_1F, SootopolisCity |
| 6.R1 | Team Magma's revenge (D-247): two grunts out of Juan's Gym door; out of Sootopolis, up Ever Grande's waterfall<br>`SootopolisCity_EventScript_DraconidRevengeAmbush` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity (31, 34) → EverGrandeCity (16, 57) (17, 57) (18, 57) … | ok, 270 steps via SootopolisCity, Fly to MossdeepCity, Route127, Route128, EverGrandeCity |
| 6.R2 | Two grunts on Ever Grande's shore; up the steps to the flower field<br>`EverGrandeCity_EventScript_DraconidShoreAmbush` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity (17, 57) → EverGrandeCity (19, 50) (20, 50) | ok, 9 steps via EverGrandeCity |
| 6.R3 | The Aqua gauntlet (five grunts, Shelly); to Victory Road's mouth<br>`EverGrandeCity_EventScript_DraconidAquaGauntlet` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity (19, 50) → EverGrandeCity (18, 43) | ok, 8 steps via EverGrandeCity |
| 6.R4 | Maxie #2 at Victory Road's mouth; into Victory Road<br>`EverGrandeCity_EventScript_DraconidMaxie` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity (18, 43) → VictoryRoad_1F (2, 23) | ok, 33 steps via EverGrandeCity, VictoryRoad_1F |
| 6.01 | Wally at the Victory Road entrance; down to B1F<br>`VictoryRoad_1F_EventScript_WallyBattleTrigger1` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | VictoryRoad_1F (2, 23) → VictoryRoad_B1F (22, 23) | ok, 136 steps via VictoryRoad_1F, EverGrandeCity, VictoryRoad_1F, VictoryRoad_B1F |
| 6.R5 | Tabitha + Courtney in Victory Road B1F; out of Victory Road<br>`VictoryRoad_B1F_EventScript_DraconidAdmins` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | VictoryRoad_B1F (22, 23) → EverGrandeCity (25, 26) (26, 26) (27, 26) | ok, 77 steps via VictoryRoad_B1F, VictoryRoad_1F, EverGrandeCity |
| 6.R6 | A grunt on the stairs out of Victory Road; to the League's forecourt<br>`EverGrandeCity_EventScript_DraconidExitGrunt` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity (26, 26) → EverGrandeCity (16, 14) (17, 14) (18, 14) … | ok, 9 steps via EverGrandeCity |
| 6.R7 | The last two grunts; to the League door<br>`EverGrandeCity_EventScript_DraconidLeagueGrunts` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity (18, 14) → EverGrandeCity_PokemonLeague_1F (entering) | ok, 2 steps via EverGrandeCity, EverGrandeCity_PokemonLeague_1F |
| 6.02 | The League guards check the badges, up to Sidney<br>`EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_PokemonLeague_1F (9, 11) → EverGrandeCity_SidneysRoom (entering) | ok, 22 steps via EverGrandeCity_PokemonLeague_1F, EverGrandeCity_Hall5, EverGrandeCity_SidneysRoom |
| 6.03 | Sidney (the door shuts behind the player), on to Phoebe<br>`EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_SidneysRoom_EventScript_Sidney` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_SidneysRoom (6, 7) → EverGrandeCity_PhoebesRoom (entering) | ok, 19 steps via EverGrandeCity_SidneysRoom, EverGrandeCity_Hall1, EverGrandeCity_PhoebesRoom |
| 6.04 | Phoebe, on to Glacia<br>`EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_PhoebesRoom_EventScript_Phoebe` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_PhoebesRoom (6, 7) → EverGrandeCity_GlaciasRoom (entering) | ok, 19 steps via EverGrandeCity_PhoebesRoom, EverGrandeCity_Hall2, EverGrandeCity_GlaciasRoom |
| 6.05 | Glacia, on to Drake<br>`EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_GlaciasRoom_EventScript_Glacia` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_GlaciasRoom (6, 7) → EverGrandeCity_DrakesRoom (entering) | ok, 19 steps via EverGrandeCity_GlaciasRoom, EverGrandeCity_Hall3, EverGrandeCity_DrakesRoom |
| 6.06 | Drake, on to the Champion<br>`EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_DrakesRoom_EventScript_Drake` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_DrakesRoom (6, 7) → EverGrandeCity_ChampionsRoom (entering) | ok, 40 steps via EverGrandeCity_DrakesRoom, EverGrandeCity_Hall4, EverGrandeCity_ChampionsRoom |
| 6.07 | Champion Steven; Brendan, Prof. Birch and May come in; to the Hall of Fame<br>`EverGrandeCity_ChampionsRoom_EventScript_EnterRoom` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_HallOfFame (7, 16) → EverGrandeCity_HallOfFame (entering) | ok, 0 steps via EverGrandeCity_HallOfFame |
| 6.08 | The Hall of Fame (no credits): home to the village bedroom<br>`EverGrandeCity_HallOfFame_EventScript_EnterHallOfFame` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_2F (entering) | ok, 0 steps via DraconidVillage_PlayersHouse_2F |
| 6.09 | Home: the celebration, the sky catches fire; downstairs<br>`DraconidVillage_PlayersHouse_2F_EventScript_DraconidHomecoming` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_1F (entering) | ok, 8 steps via DraconidVillage_PlayersHouse_2F, DraconidVillage_PlayersHouse_1F |
| 6.10 | The meteor alert on TV; the Elder's summons and his dragon to the Sky Pillar<br>`DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_Outside (17, 14) → SkyPillar_Outside (entering) | ok, 0 steps via SkyPillar_Outside |
| 6.10b | The Elder's NO: by the player's own wings from home to the Sky Pillar *(side trip)*<br>– | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_1F (5, 5) → SkyPillar_Outside (17, 14) | ok, 380 steps via DraconidVillage_PlayersHouse_1F, DraconidVillage, Fly to MossdeepCity, Route127, Route128, Route129, Route130, Route131, SkyPillar_Entrance, SkyPillar_Outside |
| 7.01 | Sky Pillar, outside: the Elder's PokéNav call (the shrine's seal has woken); his dragon flies the player home; up to the shrine<br>`SkyPillar_Outside_EventScript_DraconidElderCall` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (19, 6) → DraconidVillage_Shrine (entering) | ok, 2 steps via DraconidVillage, DraconidVillage_Shrine |
| 7.02 | The shrine: the Guardian's statue grinds aside, the carved wall opens; down to the depths<br>`DraconidVillage_Shrine_EventScript_DraconidSealScene` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_Shrine (10, 11) → DraconidVillage_Shrine_Depths next to (8, 7) | ok, 13 steps via DraconidVillage_Shrine, DraconidVillage_Shrine_Depths |
| 7.03 | Regidrago in the shrine depths (won, caught or fled); back up to the Elder<br>`DraconidVillage_Shrine_Depths_EventScript_Regidrago` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_Shrine_Depths (8, 8) → DraconidVillage_Shrine (entering) | ok, 4 steps via DraconidVillage_Shrine_Depths, DraconidVillage_Shrine |
| 7.04 | The Elder's lift back to the Sky Pillar<br>`DraconidVillage_Shrine_EventScript_DraconidElderAfterRegidrago` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_Outside (17, 14) → SkyPillar_Outside (entering) | ok, 0 steps via SkyPillar_Outside |
| 7.04b | The Elder's NO: by the player's own wings from the shrine to the Sky Pillar *(side trip)*<br>– | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_Shrine (10, 5) → SkyPillar_Outside (17, 14) | ok, 390 steps via DraconidVillage_Shrine, DraconidVillage, Fly to MossdeepCity, Route127, Route128, Route129, Route130, Route131, SkyPillar_Entrance, SkyPillar_Outside |
| 7.05 | Wallace keeps the Sky Pillar (a loss doesn't white out); the map reloads for the trial<br>`SkyPillar_Outside_EventScript_DraconidWallaceScene` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_Outside (17, 14) → SkyPillar_Outside (entering) | ok, 0 steps via SkyPillar_Outside |
| 7.06 | The Trial of Three (the player + Nerine vs Aster); the door opens, the climb<br>`SkyPillar_Outside_EventScript_DraconidTrialOfThree` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_3F (3, 2) → SkyPillar_3F (entering) | ok, 0 steps via SkyPillar_3F |
| 7.07 | Zinnia on the Sky Pillar 3F; on to the summit<br>`SkyPillar_3F_EventScript_DraconidZinniaScene` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_Top (14, 12) → SkyPillar_Top (entering) | ok, 0 steps via SkyPillar_Top |
| 7.08 | The summit: Rayquaza, Dragon Ascent, Deoxys, Mega Rayquaza breaks the meteor; the alarm (May's call), on to the village<br>`SkyPillar_Top_EventScript_DraconidSummit` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (19, 24) → DraconidVillage (entering) | ok, 0 steps via DraconidVillage |
| 7.09 | The village under attack: Brendan, May and Wally land beside the player; to Wally's house<br>`DraconidVillage_EventScript_DraconidArrival` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (19, 24) → DraconidVillage next to (15, 24) | ok, 3 steps via DraconidVillage |
| 7.10 | The south-west house: Wally + the player vs a Magma and an Aqua grunt; to the player's house<br>`DraconidVillage_EventScript_DraconidHouse2` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (16, 24) → DraconidVillage next to (11, 15) | ok, 3 steps via DraconidVillage |
| 7.11 | The player's house: May + the player vs two grunts; to the house by the pond<br>`DraconidVillage_EventScript_DraconidPlayersHouse` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (10, 15) → DraconidVillage next to (26, 18) | ok, 18 steps via DraconidVillage |
| 7.12 | The house by the pond: Brendan + the player vs two grunts, every house freed; up to Aster<br>`DraconidVillage_EventScript_DraconidHouse1` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (25, 18) → DraconidVillage next to (21, 10) | ok, 11 steps via DraconidVillage |
| 7.13 | Aster + the player vs Tabitha and Shelly; Maxie and Archie come down to the shrine (the map reloads)<br>`DraconidVillage_EventScript_DraconidAster` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (19, 11) → DraconidVillage (entering) | ok, 0 steps via DraconidVillage |
| 7.14 | Maxie and Archie: Brendan or May beside the player, the Primal multi battle; Rayquaza calms Groudon and Kyogre, the Orbs (that evening)<br>`DraconidVillage_EventScript_DraconidFinalIntro` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (19, 10) → DraconidVillage (entering) | ok, 0 steps via DraconidVillage |
| 7.15 | The goodbyes; the save, the credits from the village, home to the bedroom<br>`DraconidVillage_EventScript_DraconidGoodbyes` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_2F (entering) | ok, 0 steps via DraconidVillage_PlayersHouse_2F |
| 7.16 | Waking up after the finale; downstairs<br>`DraconidVillage_PlayersHouse_2F_EventScript_DraconidWakeUpAfterFinale` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_2F (3, 4) → DraconidVillage_PlayersHouse_1F (entering) | ok, 8 steps via DraconidVillage_PlayersHouse_2F, DraconidVillage_PlayersHouse_1F |
| 7.17 | The Elder brings the SS Ticket, the Lati news (end of Act 7)<br>`DraconidVillage_PlayersHouse_1F_EventScript_SSTicketAndLatiTV` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_1F (5, 3) → DraconidVillage next to (28, 7) | ok, 37 steps via DraconidVillage_PlayersHouse_1F, DraconidVillage |
| P.01 | Post-game: Nerine by the village pond<br>`DraconidVillage_EventScript_DraconidNerine` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (27, 7) → DraconidVillage_Shrine next to (10, 11) | ok, 18 steps via DraconidVillage, DraconidVillage_Shrine |
| P.02 | Post-game: Aster at the shrine<br>`DraconidVillage_Shrine_EventScript_Aster` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_Shrine (10, 12) → LittlerootTown (entering) | ok, 9 steps via DraconidVillage_Shrine, DraconidVillage, Fly to LittlerootTown |
| P.02b | Lance (D-261): out of the player's house onto the fly spot on a later visit, his Dragonite lands; the battle, Dratini and the Dragoninite; down the path past him to the gate *(side trip)*<br>`DraconidVillage_EventScript_LanceArrives` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage (13, 14) → DraconidVillage (19, 26) | ok, 18 steps via DraconidVillage |
| P.03 | Littleroot: Prof. Birch's National Dex; out of the lab and back in to May<br>`LittlerootTown_EventScript_BeginDexUpgradeScene`<br>`LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | LittlerootTown_ProfessorBirchsLab (6, 5) → LittlerootTown_ProfessorBirchsLab next to (5, 10) | ok, 11 steps via LittlerootTown_ProfessorBirchsLab, LittlerootTown, LittlerootTown_ProfessorBirchsLab |
| P.04 | May's post-game battle in the lab<br>`LittlerootTown_ProfessorBirchsLab_EventScript_Rival` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | LittlerootTown_ProfessorBirchsLab (6, 10) → LittlerootTown_ProfessorBirchsLab next to (8, 10) | ok, 1 steps via LittlerootTown_ProfessorBirchsLab |
| P.05 | Brendan's post-game battle in the lab<br>`LittlerootTown_ProfessorBirchsLab_EventScript_Brendan` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | LittlerootTown_ProfessorBirchsLab (7, 10) → LittlerootTown_ProfessorBirchsLab next to (5, 10) | ok, 1 steps via LittlerootTown_ProfessorBirchsLab |
| P.06 | Brendan and May together (a double); to the Slateport harbor<br>`LittlerootTown_ProfessorBirchsLab_EventScript_Rival` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | LittlerootTown_ProfessorBirchsLab (6, 10) → SlateportCity_Harbor next to (8, 10) | ok, 32 steps via LittlerootTown_ProfessorBirchsLab, LittlerootTown, Fly to SlateportCity, SlateportCity_Harbor |
| P.07 | The SS Tidal from Slateport (the SS Ticket)<br>`SlateportCity_Harbor_EventScript_FerryAttendant` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SSTidalCorridor (1, 10) → SSTidalCorridor (entering) | ok, 0 steps via SSTidalCorridor |
| P.08 | On board: Scott's Battle Frontier invitation, the crossing, off at Lilycove<br>`SSTidalCorridor_EventScript_ScottScene`<br>`SSTidalCorridor_EventScript_DepartSlateportForLilycove`<br>`SSTidalCorridor_EventScript_ExitSailor` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | LilycoveCity_Harbor (8, 11) → LilycoveCity_Harbor next to (8, 10) | ok, 0 steps via LilycoveCity_Harbor |
| P.09 | The ferry from Lilycove to the Battle Frontier; to Blue by the Battle Tower<br>`LilycoveCity_Harbor_EventScript_FerryAttendant` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | BattleFrontier_OutsideWest (19, 67) → BattleFrontier_OutsideEast next to (18, 15) | ok, 118 steps via BattleFrontier_OutsideWest, BattleFrontier_ReceptionGate, BattleFrontier_OutsideWest, BattleFrontier_OutsideEast |
| P.10 | The Battle Frontier legends: Blue<br>`BattleFrontier_OutsideEast_EventScript_DraconidBlue` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | BattleFrontier_OutsideEast (17, 15) → BattleFrontier_OutsideEast next to (29, 10) | ok, 36 steps via BattleFrontier_OutsideEast |
| P.11 | The Battle Frontier legends: Red below Artisan Cave<br>`BattleFrontier_OutsideEast_EventScript_DraconidRed` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | BattleFrontier_OutsideEast (28, 10) → BattleFrontier_OutsideEast next to (58, 22) | ok, 61 steps via BattleFrontier_OutsideEast |
| P.12 | The Battle Frontier legends: Wes in the Pyramid's sands<br>`BattleFrontier_OutsideEast_EventScript_DraconidWes` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | BattleFrontier_OutsideEast (57, 22) → BattleFrontier_OutsideEast next to (14, 15) | ok, 48 steps via BattleFrontier_OutsideEast |
| P.13 | The LEGENDS' TAG by the Battle Tower; the ferry back to Slateport<br>`BattleFrontier_OutsideEast_EventScript_DraconidTagAttendant` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | BattleFrontier_OutsideEast (14, 16) → BattleFrontier_OutsideWest next to (19, 68) | ok, 72 steps via BattleFrontier_OutsideEast, BattleFrontier_OutsideWest, BattleFrontier_ReceptionGate, BattleFrontier_OutsideWest |
| P.14 | The ferry back from the Battle Frontier; to the Sky Pillar summit<br>`BattleFrontier_OutsideWest_EventScript_FerryAttendant` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SlateportCity_Harbor (8, 11) → SkyPillar_Top next to (14, 7) | ok, 604 steps via SlateportCity_Harbor, SlateportCity, Fly to MossdeepCity, Route127, Route128, Route129, Route130, Route131, SkyPillar_Entrance, SkyPillar_Outside, SkyPillar_1F, SkyPillar_2F, SkyPillar_3F, SkyPillar_4F, SkyPillar_3F, SkyPillar_4F, SkyPillar_5F, SkyPillar_Top |
| P.15 | Deoxys on the Sky Pillar summit, where it fell; to the League<br>`SkyPillar_Top_EventScript_DraconidDeoxys` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SkyPillar_Top (14, 8) → EverGrandeCity_SidneysRoom (entering) | ok, 24 steps via SkyPillar_Top, Fly to EverGrandeCity, EverGrandeCity_PokemonLeague_1F, EverGrandeCity_Hall5, EverGrandeCity_SidneysRoom |
| P.16 | The League again: Sidney (the Hall of Fame reset the Elite Four)<br>`EverGrandeCity_SidneysRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_SidneysRoom_EventScript_Sidney` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_SidneysRoom (6, 7) → EverGrandeCity_PhoebesRoom (entering) | ok, 19 steps via EverGrandeCity_SidneysRoom, EverGrandeCity_Hall1, EverGrandeCity_PhoebesRoom |
| P.17 | Phoebe<br>`EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_PhoebesRoom_EventScript_Phoebe` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_PhoebesRoom (6, 7) → EverGrandeCity_GlaciasRoom (entering) | ok, 19 steps via EverGrandeCity_PhoebesRoom, EverGrandeCity_Hall2, EverGrandeCity_GlaciasRoom |
| P.18 | Glacia<br>`EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_GlaciasRoom_EventScript_Glacia` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_GlaciasRoom (6, 7) → EverGrandeCity_DrakesRoom (entering) | ok, 19 steps via EverGrandeCity_GlaciasRoom, EverGrandeCity_Hall3, EverGrandeCity_DrakesRoom |
| P.19 | Drake<br>`EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor`<br>`EverGrandeCity_DrakesRoom_EventScript_Drake` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | EverGrandeCity_DrakesRoom (6, 7) → EverGrandeCity_ChampionsRoom (entering) | ok, 40 steps via EverGrandeCity_DrakesRoom, EverGrandeCity_Hall4, EverGrandeCity_ChampionsRoom |
| P.20 | Steven's rematch, the Hall of Fame again (home to the bedroom); to Sootopolis<br>`EverGrandeCity_ChampionsRoom_EventScript_EnterRoom`<br>`EverGrandeCity_HallOfFame_EventScript_EnterHallOfFame` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | DraconidVillage_PlayersHouse_2F (3, 4) → SootopolisCity next to (31, 19) | ok, 134 steps via DraconidVillage_PlayersHouse_2F, DraconidVillage_PlayersHouse_1F, DraconidVillage, Fly to SootopolisCity |
| P.21 | Wallace by the Cave of Origin<br>`SootopolisCity_EventScript_DraconidPostgameWallace` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | SootopolisCity (31, 20) → MeteorFalls_StevensCave next to (19, 3) | ok, 279 steps via SootopolisCity, Fly to RustboroCity, Route115, MeteorFalls_1F_1R, MeteorFalls_1F_2R, MeteorFalls_B1F_1R, MeteorFalls_1F_1R, MeteorFalls_StevensCave |
| P.22 | Steven's hideaway in Meteor Falls<br>`MeteorFalls_StevensCave_EventScript_DraconidSteven` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | – | ok |
| 7x.01 | Post-game (D-208): Groudon asleep in the Magma Hideout, the ledge below the magma pool *(side trip)*<br>`MagmaHideout_4F_EventScript_DraconidGroudon` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | MeteorFalls_StevensCave (19, 4) → MagmaHideout_4F next to (16, 20) | ok, 508 steps via MeteorFalls_StevensCave, MeteorFalls_1F_1R, MeteorFalls_B1F_1R, MeteorFalls_1F_2R, MeteorFalls_1F_1R, Route115, Fly to LavaridgeTown, Route112, JaggedPass, MagmaHideout_1F, MagmaHideout_2F_1R, MagmaHideout_3F_1R, MagmaHideout_4F |
| 7x.02 | Post-game (D-208): Kyogre asleep in the Seafloor Cavern, from the shore of the deep pool *(side trip)*<br>`SeafloorCavern_Room9_EventScript_DraconidKyogreSpot` | 8 / Rock Smash, Strength, Surf, Fly, Dive, Waterfall | MeteorFalls_StevensCave (19, 4) → SeafloorCavern_Room9 next to (17, 41) | ok, 445 steps via MeteorFalls_StevensCave, MeteorFalls_1F_1R, MeteorFalls_B1F_1R, MeteorFalls_1F_2R, MeteorFalls_1F_1R, Route115, Fly to MossdeepCity, Route127, Route128, Underwater_Route128, Underwater_SeafloorCavern, SeafloorCavern_Entrance, SeafloorCavern_Room1, SeafloorCavern_Room2, SeafloorCavern_Room7, SeafloorCavern_Room3, SeafloorCavern_Room8, SeafloorCavern_Room9 |

## Round 1 battles and what a loss does

Generated by `python3 tools/hack/check_hardlock.py --battles --markdown`. "The way back is open from …": the Pokémon
Centers the story passed in that act and the one before (any may have been the last one used), each checked with its
own Mr. Briney spot. A loss that goes on names what it leads to (the village's way home, a retry). Battles of
scenes outside the story table get the static check only.

| Where | Opponents | After a loss |
|---|---|---|
| `data/maps/AquaHideout_B2F/scripts.inc:27 AquaHideout_B2F_EventScript_Matt` | MATT | whites out; leg 5.01: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, LilycoveCity |
| `data/maps/DraconidPass/scripts.inc:23 DraconidPass_EventScript_AsterBattle_1` | ASTER_PASS_DEINO | goes on (FLAG_DRACONID_NO_WHITEOUT) |
| `data/maps/DraconidVillage_Shrine_Depths/scripts.inc:44 DraconidVillage_Shrine_Depths_EventScript_Regidrago_1` | StartRegiBattle | whites out; leg 7.03: the scene starts again; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| `data/maps/EverGrandeCity_ChampionsRoom/scripts.inc:44 EverGrandeCity_ChampionsRoom_EventScript_Wallace` | STEVEN | whites out; leg 6.07: back through EverGrandeCity_ChampionsRoom (the Champion's room (vanilla): the Hall of Fame is the only way on) |
| `data/maps/PetalburgWoods/scripts.inc:29 PetalburgWoods_EventScript_DevonResearcherLeft` | NERINE_PETALBURG_WOODS_DEINO | whites out; leg 1.13: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity |
| `data/maps/PetalburgWoods/scripts.inc:65 PetalburgWoods_EventScript_DevonResearcherRight` | NERINE_PETALBURG_WOODS_DEINO | whites out; the scene can start again (not in the story table: no walk back checked) |
| `data/maps/RusturfTunnel/scripts.inc:304 RusturfTunnel_EventScript_Grunt` | NERINE_RUSTURF_DEINO_CHARMANDER | whites out; leg 2.04: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| `data/maps/SeafloorCavern_Room9/scripts.inc:39 SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre` | ARCHIE | whites out; leg 5.08: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| `data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc:30 SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | GRUNT_MUSEUM_1 | whites out; leg 2.13: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity |
| `data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc:38 SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | NERINE_SLATEPORT_DEINO_CHARMANDER | whites out; leg 2.13: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity |
| `data/scripts/draconid/act1.inc:127 RustboroCity_EventScript_DraconidBrendan` | BRENDAN_RUSTBORO | whites out; leg 1.15: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| `data/scripts/draconid/act3.inc:111 MeteorFalls_1F_1R_EventScript_DraconidAster` | ASTER_METEOR_FALLS_DEINO | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/act3.inc:354 MtChimney_EventScript_DraconidNerine` | NERINE_MT_CHIMNEY_DEINO_CHARMANDER | whites out; leg 3.03: the scene starts again; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown |
| `data/scripts/draconid/act3.inc:378 MtChimney_EventScript_DraconidBrendan` | BRENDAN_MT_CHIMNEY | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/act4.inc:133 PetalburgCity_EventScript_DraconidWallyTrigger` | WALLY_PETALBURG | whites out; leg 4.01: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity |
| `data/scripts/draconid/act4.inc:350 LilycoveCity_EventScript_DraconidRivals_1` | BRENDAN_LILYCOVE, MAY_LILYCOVE | whites out; leg 4.10: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| `data/scripts/draconid/act4.inc:423 LilycoveCity_EventScript_DraconidWally` | WALLY_LILYCOVE | whites out; leg 4.11: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| `data/scripts/draconid/act4.inc:546 MtPyre_Summit_EventScript_DraconidNerine_1` | NERINE_MT_PYRE_DEINO_CHARMANDER | whites out; leg 4.13: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| `data/scripts/draconid/act5.inc:127 MossdeepCity_SpaceCenter_2F_EventScript_DraconidTagBattle_2` | STEVEN_MOSSDEEP, BRENDAN_MOSSDEEP | goes on (FLAG_DRACONID_NO_WHITEOUT) |
| `data/scripts/draconid/act5.inc:25 AquaHideout_B2F_EventScript_DraconidNerineBattle` | NERINE_AQUA_HIDEOUT_DEINO_CHARMANDER | whites out; leg 5.01: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, LilycoveCity |
| `data/scripts/draconid/act5.inc:354 SeafloorCavern_Room9_EventScript_DraconidNerineReveal` | NERINE_SEAFLOOR_DEINO_CHARMANDER | whites out; leg 5.07: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| `data/scripts/draconid/act5.inc:397 SootopolisCity_EventScript_DraconidMaxie_9` | MAXIE_SOOTOPOLIS | whites out; leg 5.11: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, SootopolisCity, LilycoveCity |
| `data/scripts/draconid/act5.inc:576 SootopolisCity_EventScript_DraconidMultiBattle_10` | MAXIE_SOOTOPOLIS_MULTI, ARCHIE_SOOTOPOLIS_MULTI | goes on (a multi battle) |
| `data/scripts/draconid/act5.inc:641 SootopolisCity_EventScript_DraconidMultiBattle_14` | MAXIE_SOOTOPOLIS_MULTI, ARCHIE_SOOTOPOLIS_MULTI | goes on (a multi battle) |
| `data/scripts/draconid/act6.inc:100 SootopolisCity_EventScript_DraconidPostgameWallace_1` | WALLACE | whites out; leg P.21: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast, MossdeepCity, EverGrandeCity, EverGrandeCity, SootopolisCity |
| `data/scripts/draconid/act7.inc:139 SkyPillar_Outside_EventScript_DraconidDoubleBattle` | ASTER_SKY_PILLAR_DEINO | goes on (FLAG_DRACONID_NO_WHITEOUT); leg 7.06: talking to LOCALID_SKY_PILLAR_OUTSIDE_ASTER fights again and re-entering SkyPillar_Outside starts the scene again |
| `data/scripts/draconid/act7.inc:290 SkyPillar_3F_EventScript_DraconidBattleZinnia` | ZINNIA_SKY_PILLAR | goes on (FLAG_DRACONID_NO_WHITEOUT); leg 7.07: talking to LOCALID_SKY_PILLAR_3F_ZINNIA fights again and re-entering SkyPillar_3F starts the scene again |
| `data/scripts/draconid/act7.inc:477 SkyPillar_Top_EventScript_DraconidCatchRayquaza_3` | BattleSetup_StartLegendaryBattle | goes on (FLAG_DRACONID_NO_WHITEOUT) |
| `data/scripts/draconid/act7.inc:584 SkyPillar_Top_EventScript_DraconidDeoxysAttacks_3` | BattleSetup_StartLegendaryBattle | goes on (FLAG_DRACONID_NO_WHITEOUT) |
| `data/scripts/draconid/act7.inc:738 SkyPillar_Top_EventScript_DraconidDeoxys` | BattleSetup_StartLegendaryBattle | whites out; leg P.15: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast, MossdeepCity |
| `data/scripts/draconid/act7.inc:801 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_8` | MAY_POSTGAME | whites out; leg P.04: the scene starts again; the way back is open from DraconidVillage, LittlerootTown |
| `data/scripts/draconid/act7.inc:824 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5` | BRENDAN_POSTGAME | whites out; leg P.05: the scene starts again; the way back is open from DraconidVillage, LittlerootTown |
| `data/scripts/draconid/act7.inc:900 DraconidVillage_Shrine_EventScript_Aster` | ASTER_POSTGAME_DEINO | whites out; leg P.02: the scene starts again; the way back is open from DraconidVillage |
| `data/scripts/draconid/act7.inc:926 DraconidVillage_EventScript_DraconidNerine` | NERINE_POSTGAME_DEINO_CHARMANDER | whites out; leg P.01: the scene starts again; the way back is open from DraconidVillage |
| `data/scripts/draconid/act7x.inc:1043 DraconidVillage_EventScript_DraconidFinalChoice_1` | MAXIE_FINALE, ARCHIE_FINALE | goes on (a multi battle); leg 7.14: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_MAXIE fights again; the way back is open |
| `data/scripts/draconid/act7x.inc:1067 DraconidVillage_EventScript_DraconidFinalChoice_6` | MAXIE_FINALE, ARCHIE_FINALE | goes on (a multi battle); leg 7.14: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_MAXIE fights again; the way back is open |
| `data/scripts/draconid/act7x.inc:1307 MagmaHideout_4F_EventScript_DraconidGroudon` | BattleSetup_StartLegendaryBattle | whites out; leg 7x.01: the scene starts again; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| `data/scripts/draconid/act7x.inc:1355 SeafloorCavern_Room9_EventScript_DraconidKyogre` | BattleSetup_StartLegendaryBattle | whites out; leg 7x.02: the scene starts again; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| `data/scripts/draconid/act7x.inc:709 DraconidVillage_EventScript_DraconidHouse2_1` | GRUNT_VILLAGE_1, GRUNT_VILLAGE_2 | goes on (a multi battle); leg 7.10: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_WALLY starts it again; the way back is open |
| `data/scripts/draconid/act7x.inc:752 DraconidVillage_EventScript_DraconidPlayersHouse_1` | GRUNT_VILLAGE_3, GRUNT_VILLAGE_4 | goes on (a multi battle); leg 7.11: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_MAY starts it again; the way back is open |
| `data/scripts/draconid/act7x.inc:795 DraconidVillage_EventScript_DraconidHouse1_1` | GRUNT_VILLAGE_5, GRUNT_VILLAGE_6 | goes on (a multi battle); leg 7.12: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_BRENDAN starts it again; the way back is open |
| `data/scripts/draconid/act7x.inc:84 SkyPillar_Outside_EventScript_DraconidBattleWallace` | WALLACE_SKY_PILLAR | goes on (FLAG_DRACONID_NO_WHITEOUT); leg 7.05: talking to LOCALID_SKY_PILLAR_WALLACE fights again and re-entering SkyPillar_Outside starts the scene again |
| `data/scripts/draconid/act7x.inc:930 DraconidVillage_EventScript_DraconidAdminsBattle` | TABITHA_VILLAGE, SHELLY_VILLAGE | goes on (a multi battle); leg 7.13: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_ASTER starts it again; the way back is open |
| `data/scripts/draconid/birch_intro.inc:266 Route103_EventScript_DraconidMay` | MAY_ROUTE_103 | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/birch_intro.inc:46 Route101_EventScript_DraconidRescue_1` | StartBirchRescueBattle | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/frontier_legends.inc:104 BattleFrontier_OutsideEast_EventScript_DraconidBlue` | BLUE_FRONTIER | whites out; leg P.10: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| `data/scripts/draconid/frontier_legends.inc:26 BattleFrontier_OutsideEast_EventScript_DraconidWes` | WES_FRONTIER | whites out; leg P.12: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| `data/scripts/draconid/frontier_legends.inc:285 BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_12` | WES_FRONTIER_MULTI, RED_FRONTIER_MULTI | goes on (a multi battle) |
| `data/scripts/draconid/frontier_legends.inc:345 BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_17` | RED_FRONTIER_MULTI, BLUE_FRONTIER_MULTI | goes on (a multi battle) |
| `data/scripts/draconid/frontier_legends.inc:349 BattleFrontier_OutsideEast_EventScript_DraconidTagBattle_18` | WES_FRONTIER_MULTI, BLUE_FRONTIER_MULTI | goes on (a multi battle) |
| `data/scripts/draconid/frontier_legends.inc:64 BattleFrontier_OutsideEast_EventScript_DraconidRed` | RED_FRONTIER | whites out; leg P.11: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| `data/scripts/draconid/lance.inc:186 DraconidVillage_EventScript_LanceBattle` | LANCE_DRACONID | whites out; leg P.02b: talking to LOCALID_DRACONID_VILLAGE_LANCE fights again; the way back is open from DraconidVillage, LittlerootTown |
| `data/scripts/draconid/magma_revenge.inc:186 EverGrandeCity_EventScript_DraconidShoreAmbush` | GRUNT_EVER_GRANDE_SHORE_1 | whites out; leg 6.R2: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:187 EverGrandeCity_EventScript_DraconidShoreAmbush` | GRUNT_EVER_GRANDE_SHORE_2 | whites out; leg 6.R2: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:203 EverGrandeCity_EventScript_DraconidShoreAmbush_2` | GRUNT_EVER_GRANDE_SHORE_1, GRUNT_EVER_GRANDE_SHORE_2 | whites out; leg 6.R2: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:225 EverGrandeCity_EventScript_DraconidCenterGrunt` | GRUNT_EVER_GRANDE_CENTER | whites out; the scene can start again (not in the story table: no walk back checked) |
| `data/scripts/draconid/magma_revenge.inc:277 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | GRUNT_AQUA_GAUNTLET_1 | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:282 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | GRUNT_AQUA_GAUNTLET_2 | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:287 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | GRUNT_AQUA_GAUNTLET_3 | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:292 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | GRUNT_AQUA_GAUNTLET_4 | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:295 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | GRUNT_AQUA_GAUNTLET_5 | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:306 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | SHELLY_EVER_GRANDE | whites out; leg 6.R3: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:369 EverGrandeCity_EventScript_DraconidMaxie` | MAXIE_VICTORY_ROAD | whites out; leg 6.R4: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:403 EverGrandeCity_EventScript_DraconidExitGrunt_1` | GRUNT_VICTORY_ROAD_EXIT | whites out; leg 6.R6: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:451 EverGrandeCity_EventScript_DraconidLeagueGrunts_1` | GRUNT_POKEMON_LEAGUE_1 | whites out; leg 6.R7: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:452 EverGrandeCity_EventScript_DraconidLeagueGrunts_1` | GRUNT_POKEMON_LEAGUE_2 | whites out; leg 6.R7: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:484 EverGrandeCity_EventScript_DraconidLeagueGrunts_8` | GRUNT_POKEMON_LEAGUE_1, GRUNT_POKEMON_LEAGUE_2 | whites out; leg 6.R7: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:545 VictoryRoad_B1F_EventScript_DraconidAdmins` | TABITHA_VICTORY_ROAD | whites out; leg 6.R5: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:546 VictoryRoad_B1F_EventScript_DraconidAdmins` | COURTNEY_VICTORY_ROAD | whites out; leg 6.R5: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:571 VictoryRoad_B1F_EventScript_DraconidAdmins_2` | TABITHA_VICTORY_ROAD, COURTNEY_VICTORY_ROAD | whites out; leg 6.R5: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| `data/scripts/draconid/magma_revenge.inc:58 SootopolisCity_EventScript_DraconidRevengeAmbush_1` | GRUNT_SOOTOPOLIS_REVENGE_1 | whites out; leg 6.R1: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity |
| `data/scripts/draconid/magma_revenge.inc:59 SootopolisCity_EventScript_DraconidRevengeAmbush_1` | GRUNT_SOOTOPOLIS_REVENGE_2 | whites out; leg 6.R1: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity |
| `data/scripts/draconid/magma_revenge.inc:82 SootopolisCity_EventScript_DraconidRevengeAmbush_8` | GRUNT_SOOTOPOLIS_REVENGE_1, GRUNT_SOOTOPOLIS_REVENGE_2 | whites out; leg 6.R1: the scene starts again; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity |
| `data/scripts/draconid/reputation/dewford.inc:110 DewfordTown_Gym_EventScript_DraconidRepBrawly_2` | BRAWLY_1 | whites out; leg 2.08: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown |
| `data/scripts/draconid/reputation/fortree.inc:110 FortreeCity_Gym_EventScript_DraconidRepWinona_2` | WINONA_1 | whites out; leg 4.09: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity |
| `data/scripts/draconid/reputation/lavaridge.inc:126 LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_2` | FLANNERY_1 | whites out; leg 3.06: the scene starts again; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown, LavaridgeTown |
| `data/scripts/draconid/reputation/mauville.inc:116 MauvilleCity_Gym_EventScript_DraconidRepWattson_2` | WATTSON_1 | whites out; leg 2.16: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity, MauvilleCity |
| `data/scripts/draconid/reputation/mossdeep.inc:129 MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_2` | TATE_AND_LIZA_1 | whites out; leg 5.02: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| `data/scripts/draconid/reputation/rustboro.inc:168 RustboroCity_Gym_EventScript_DraconidRepRoxanne_2` | ROXANNE_1 | whites out; leg 1.16: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| `data/scripts/draconid/reputation/sootopolis.inc:97 SootopolisCity_Gym_1F_EventScript_DraconidRepJuan` | JUAN_1 | whites out; leg 5.15: the scene starts again; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, SootopolisCity, LilycoveCity |
| `data/scripts/draconid/rivals2.inc:147 LavaridgeTown_EventScript_DraconidMayBattle` | MAY_LAVARIDGE | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/rivals2.inc:20 Route104_EventScript_DraconidBrendan` | BRENDAN_ROUTE_104 | whites out; leg 2.06r: the scene starts again; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| `data/scripts/draconid/rivals2.inc:218 Route120_EventScript_DraconidWally_1` | WALLY_ROUTE_120 | whites out; leg 4.09r: the scene starts again; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity |
| `data/scripts/draconid/rivals2.inc:300 JaggedPass_EventScript_DraconidBrendan` | BRENDAN_JAGGED_PASS | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/rivals2.inc:381 MossdeepCity_EventScript_DraconidMay` | MAY_MOSSDEEP | goes on (early-rival / first battle rule) |
| `data/scripts/draconid/rivals2.inc:86 Route112_EventScript_DraconidWally_1` | WALLY_ROUTE_112 | whites out; leg 3.01r: the scene starts again; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown |

## Hard-lock notes

Generated by `python3 tools/hack/check_hardlock.py -v --markdown` (0 LOCK, 0 CHECK on the head; the notes are by design or
emulator-verified, see above).

| # | Severity | Check | Where | Finding |
|---|---|---|---|---|
| 1 | NOTE | battle | `data/maps/AquaHideout_B2F/scripts.inc:27 AquaHideout_B2F_EventScript_Matt` | leg 5.01 TRAINER_MATT: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, LilycoveCity |
| 2 | NOTE | battle | `data/maps/DraconidVillage_Shrine_Depths/scripts.inc:44 DraconidVillage_Shrine_Depths_EventScript_Regidrago_1` | leg 7.03 StartRegiBattle: a whiteout; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| 3 | NOTE | battle | `data/maps/EverGrandeCity_ChampionsRoom/scripts.inc:44 EverGrandeCity_ChampionsRoom_EventScript_Wallace` | leg 6.07 TRAINER_STEVEN: a whiteout sends the player back through EverGrandeCity_ChampionsRoom (the Champion's room (vanilla): the Hall of Fame is the only way on) |
| 4 | NOTE | battle | `data/maps/PetalburgWoods/scripts.inc:29 PetalburgWoods_EventScript_DevonResearcherLeft` | leg 1.13 TRAINER_NERINE_PETALBURG_WOODS_DEINO: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity |
| 5 | NOTE | battle | `data/maps/RusturfTunnel/scripts.inc:304 RusturfTunnel_EventScript_Grunt` | leg 2.04 TRAINER_NERINE_RUSTURF_DEINO_CHARMANDER: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| 6 | NOTE | battle | `data/maps/SeafloorCavern_Room9/scripts.inc:39 SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre` | leg 5.08 TRAINER_ARCHIE: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| 7 | NOTE | battle | `data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc:30 SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | leg 2.13 TRAINER_GRUNT_MUSEUM_1: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity |
| 8 | NOTE | battle | `data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc:38 SlateportCity_OceanicMuseum_2F_EventScript_CaptStern` | leg 2.13 TRAINER_NERINE_SLATEPORT_DEINO_CHARMANDER: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity |
| 9 | NOTE | battle | `data/scripts/draconid/act1.inc:127 RustboroCity_EventScript_DraconidBrendan` | leg 1.15 TRAINER_BRENDAN_RUSTBORO: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| 10 | NOTE | battle | `data/scripts/draconid/act3.inc:354 MtChimney_EventScript_DraconidNerine` | leg 3.03 TRAINER_NERINE_MT_CHIMNEY_DEINO_CHARMANDER: a whiteout; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown |
| 11 | NOTE | battle | `data/scripts/draconid/act4.inc:133 PetalburgCity_EventScript_DraconidWallyTrigger` | leg 4.01 TRAINER_WALLY_PETALBURG: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity |
| 12 | NOTE | battle | `data/scripts/draconid/act4.inc:350 LilycoveCity_EventScript_DraconidRivals_1` | leg 4.10 TRAINER_BRENDAN_LILYCOVE, TRAINER_MAY_LILYCOVE: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| 13 | NOTE | battle | `data/scripts/draconid/act4.inc:423 LilycoveCity_EventScript_DraconidWally` | leg 4.11 TRAINER_WALLY_LILYCOVE: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| 14 | NOTE | battle | `data/scripts/draconid/act4.inc:546 MtPyre_Summit_EventScript_DraconidNerine_1` | leg 4.13 TRAINER_NERINE_MT_PYRE_DEINO_CHARMANDER: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity, LilycoveCity |
| 15 | NOTE | battle | `data/scripts/draconid/act5.inc:25 AquaHideout_B2F_EventScript_DraconidNerineBattle` | leg 5.01 TRAINER_NERINE_AQUA_HIDEOUT_DEINO_CHARMANDER: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, LilycoveCity |
| 16 | NOTE | battle | `data/scripts/draconid/act5.inc:354 SeafloorCavern_Room9_EventScript_DraconidNerineReveal` | leg 5.07 TRAINER_NERINE_SEAFLOOR_DEINO_CHARMANDER: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| 17 | NOTE | battle | `data/scripts/draconid/act5.inc:397 SootopolisCity_EventScript_DraconidMaxie_9` | leg 5.11 TRAINER_MAXIE_SOOTOPOLIS: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, SootopolisCity, LilycoveCity |
| 18 | NOTE | battle | `data/scripts/draconid/act6.inc:100 SootopolisCity_EventScript_DraconidPostgameWallace_1` | leg P.21 TRAINER_WALLACE: a whiteout; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast, MossdeepCity, EverGrandeCity, EverGrandeCity, SootopolisCity |
| 19 | NOTE | battle | `data/scripts/draconid/act7.inc:738 SkyPillar_Top_EventScript_DraconidDeoxys` | leg P.15 BattleSetup_StartLegendaryBattle: a whiteout; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast, MossdeepCity |
| 20 | NOTE | battle | `data/scripts/draconid/act7.inc:801 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_8` | leg P.04 TRAINER_MAY_POSTGAME: a whiteout; the way back is open from DraconidVillage, LittlerootTown |
| 21 | NOTE | battle | `data/scripts/draconid/act7.inc:824 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_5` | leg P.05 TRAINER_BRENDAN_POSTGAME: a whiteout; the way back is open from DraconidVillage, LittlerootTown |
| 22 | NOTE | battle | `data/scripts/draconid/act7.inc:900 DraconidVillage_Shrine_EventScript_Aster` | leg P.02 TRAINER_ASTER_POSTGAME_DEINO: a whiteout; the way back is open from DraconidVillage |
| 23 | NOTE | battle | `data/scripts/draconid/act7.inc:926 DraconidVillage_EventScript_DraconidNerine` | leg P.01 TRAINER_NERINE_POSTGAME_DEINO_CHARMANDER: a whiteout; the way back is open from DraconidVillage |
| 24 | NOTE | battle | `data/scripts/draconid/act7x.inc:1307 MagmaHideout_4F_EventScript_DraconidGroudon` | leg 7x.01 BattleSetup_StartLegendaryBattle: a whiteout; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| 25 | NOTE | battle | `data/scripts/draconid/act7x.inc:1355 SeafloorCavern_Room9_EventScript_DraconidKyogre` | leg 7x.02 BattleSetup_StartLegendaryBattle: a whiteout; the way back is open from SootopolisCity, MossdeepCity, EverGrandeCity, DraconidVillage_PlayersHouse_2F, EverGrandeCity |
| 26 | NOTE | battle | `data/scripts/draconid/frontier_legends.inc:104 BattleFrontier_OutsideEast_EventScript_DraconidBlue` | leg P.10 TRAINER_BLUE_FRONTIER: a whiteout; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| 27 | NOTE | battle | `data/scripts/draconid/frontier_legends.inc:26 BattleFrontier_OutsideEast_EventScript_DraconidWes` | leg P.12 TRAINER_WES_FRONTIER: a whiteout; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| 28 | NOTE | battle | `data/scripts/draconid/frontier_legends.inc:64 BattleFrontier_OutsideEast_EventScript_DraconidRed` | leg P.11 TRAINER_RED_FRONTIER: a whiteout; the way back is open from DraconidVillage, LittlerootTown, SlateportCity, BattleFrontier_OutsideEast |
| 29 | NOTE | battle | `data/scripts/draconid/lance.inc:186 DraconidVillage_EventScript_LanceBattle` | leg P.02b TRAINER_LANCE_DRACONID: a whiteout; the way back is open from DraconidVillage, LittlerootTown |
| 30 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:186 EverGrandeCity_EventScript_DraconidShoreAmbush` | leg 6.R2 TRAINER_GRUNT_EVER_GRANDE_SHORE_1: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 31 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:187 EverGrandeCity_EventScript_DraconidShoreAmbush` | leg 6.R2 TRAINER_GRUNT_EVER_GRANDE_SHORE_2: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 32 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:277 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_GRUNT_AQUA_GAUNTLET_1: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 33 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:282 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_GRUNT_AQUA_GAUNTLET_2: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 34 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:287 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_GRUNT_AQUA_GAUNTLET_3: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 35 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:292 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_GRUNT_AQUA_GAUNTLET_4: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 36 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:295 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_GRUNT_AQUA_GAUNTLET_5: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 37 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:306 EverGrandeCity_EventScript_DraconidAquaGauntlet_1` | leg 6.R3 TRAINER_SHELLY_EVER_GRANDE: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 38 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:369 EverGrandeCity_EventScript_DraconidMaxie` | leg 6.R4 TRAINER_MAXIE_VICTORY_ROAD: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 39 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:403 EverGrandeCity_EventScript_DraconidExitGrunt_1` | leg 6.R6 TRAINER_GRUNT_VICTORY_ROAD_EXIT: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 40 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:451 EverGrandeCity_EventScript_DraconidLeagueGrunts_1` | leg 6.R7 TRAINER_GRUNT_POKEMON_LEAGUE_1: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 41 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:452 EverGrandeCity_EventScript_DraconidLeagueGrunts_1` | leg 6.R7 TRAINER_GRUNT_POKEMON_LEAGUE_2: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 42 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:545 VictoryRoad_B1F_EventScript_DraconidAdmins` | leg 6.R5 TRAINER_TABITHA_VICTORY_ROAD: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 43 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:546 VictoryRoad_B1F_EventScript_DraconidAdmins` | leg 6.R5 TRAINER_COURTNEY_VICTORY_ROAD: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity, EverGrandeCity |
| 44 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:58 SootopolisCity_EventScript_DraconidRevengeAmbush_1` | leg 6.R1 TRAINER_GRUNT_SOOTOPOLIS_REVENGE_1: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity |
| 45 | NOTE | battle | `data/scripts/draconid/magma_revenge.inc:59 SootopolisCity_EventScript_DraconidRevengeAmbush_1` | leg 6.R1 TRAINER_GRUNT_SOOTOPOLIS_REVENGE_2: a whiteout; the way back is open from LilycoveCity, MossdeepCity, SootopolisCity |
| 46 | NOTE | battle | `data/scripts/draconid/reputation/dewford.inc:110 DewfordTown_Gym_EventScript_DraconidRepBrawly_2` | leg 2.08 TRAINER_BRAWLY_1: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown |
| 47 | NOTE | battle | `data/scripts/draconid/reputation/fortree.inc:110 FortreeCity_Gym_EventScript_DraconidRepWinona_2` | leg 4.09 TRAINER_WINONA_1: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity |
| 48 | NOTE | battle | `data/scripts/draconid/reputation/lavaridge.inc:126 LavaridgeTown_Gym_1F_EventScript_DraconidRepFlannery_2` | leg 3.06 TRAINER_FLANNERY_1: a whiteout; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown, LavaridgeTown |
| 49 | NOTE | battle | `data/scripts/draconid/reputation/mauville.inc:116 MauvilleCity_Gym_EventScript_DraconidRepWattson_2` | leg 2.16 TRAINER_WATTSON_1: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity, DewfordTown, SlateportCity, MauvilleCity |
| 50 | NOTE | battle | `data/scripts/draconid/reputation/mossdeep.inc:129 MossdeepCity_Gym_EventScript_DraconidRepTateAndLiza_2` | leg 5.02 TRAINER_TATE_AND_LIZA_1: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, LilycoveCity |
| 51 | NOTE | battle | `data/scripts/draconid/reputation/rustboro.inc:168 RustboroCity_Gym_EventScript_DraconidRepRoxanne_2` | leg 1.16 TRAINER_ROXANNE_1: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| 52 | NOTE | battle | `data/scripts/draconid/reputation/sootopolis.inc:97 SootopolisCity_Gym_1F_EventScript_DraconidRepJuan` | leg 5.15 TRAINER_JUAN_1: a whiteout; the way back is open from PetalburgCity, OldaleTown, MauvilleCity, FortreeCity, LavaridgeTown, MossdeepCity, SootopolisCity, LilycoveCity |
| 53 | NOTE | battle | `data/scripts/draconid/rivals2.inc:20 Route104_EventScript_DraconidBrendan` | leg 2.06r TRAINER_BRENDAN_ROUTE_104: a whiteout; the way back is open from DraconidVillage, LittlerootTown, OldaleTown, PetalburgCity, RustboroCity |
| 54 | NOTE | battle | `data/scripts/draconid/rivals2.inc:218 Route120_EventScript_DraconidWally_1` | leg 4.09r TRAINER_WALLY_ROUTE_120: a whiteout; the way back is open from FallarborTown, LavaridgeTown, MauvilleCity, VerdanturfTown, RustboroCity, PetalburgCity, OldaleTown, FortreeCity |
| 55 | NOTE | battle | `data/scripts/draconid/rivals2.inc:86 Route112_EventScript_DraconidWally_1` | leg 3.01r TRAINER_WALLY_ROUTE_112: a whiteout; the way back is open from RustboroCity, DewfordTown, SlateportCity, MauvilleCity, FallarborTown |
| 56 | NOTE | coord | `data/scripts/draconid/act4.inc:174 Route119_EventScript_DraconidTabithaOrder` | Route119_EventScript_DraconidTabithaOrder (6, 33): this path leaves VAR_WEATHER_INSTITUTE_STATE and the player where they were; stepping back on starts it again, stepping off to (6, 34), (6, 32), (7, 33) doesn't |
| 57 | NOTE | reentry | `data/maps/DraconidVillage_Shrine_Depths/scripts.inc:61 DraconidVillage_Shrine_Depths_EventScript_Regidrago_9` | leg 7.03 DraconidVillage_Shrine_Depths_EventScript_Regidrago: gives control back before the scene is done (a choice at DraconidVillage_Shrine_Depths_EventScript_Regidrago_1, DraconidVillage_Shrine_Depths_EventScript_Regidrago_9); talking to LOCALID_SHRINE_DEPTHS_REGIDRAGO tries again and re-entering the map starts it again |
| 58 | NOTE | reentry | `data/maps/DraconidVillage_Shrine_Depths/scripts.inc:70 DraconidVillage_Shrine_Depths_EventScript_Regidrago_5` | leg 7.03 DraconidVillage_Shrine_Depths_EventScript_Regidrago: gives control back before the scene is done (a choice at DraconidVillage_Shrine_Depths_EventScript_Regidrago_1); talking to LOCALID_SHRINE_DEPTHS_REGIDRAGO tries again and re-entering the map starts it again |
| 59 | NOTE | reentry | `data/maps/MauvilleCity_BikeShop/scripts.inc:14 MauvilleCity_BikeShop_EventScript_Rydel` | leg 2.18 MauvilleCity_BikeShop_EventScript_Rydel: gives control back before the scene is done (a choice at MauvilleCity_BikeShop_EventScript_Rydel); talking to object 1 tries again and re-entering the map starts it again |
| 60 | NOTE | reentry | `data/maps/MauvilleCity_BikeShop/scripts.inc:29 MauvilleCity_BikeShop_EventScript_ChooseBike` | leg 2.18 MauvilleCity_BikeShop_EventScript_Rydel: gives control back before the scene is done (a choice at MauvilleCity_BikeShop_EventScript_ChooseBike, MauvilleCity_BikeShop_EventScript_Rydel); talking to object 1 tries again and re-entering the map starts it again |
| 61 | NOTE | reentry | `data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc:31 SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee` | leg 2.12 SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft: gives control back before the scene is done (a choice at SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee); re-entering the map starts it again |
| 62 | NOTE | reentry | `data/scripts/draconid/act3.inc:658 LavaridgeTown_EventScript_DraconidTraveller_8` | leg 3.05 LavaridgeTown_EventScript_DraconidTraveller: gives control back before the scene is done (a choice at LavaridgeTown_EventScript_DraconidTraveller); talking to LOCALID_LAVARIDGE_DRACONID_TRAVELLER tries again and re-entering the map starts it again |
| 63 | NOTE | reentry | `data/scripts/draconid/act4.inc:388 LilycoveCity_EventScript_DraconidRivals_9` | leg 4.10 LilycoveCity_EventScript_Rival: gives control back before the scene is done (a choice at LilycoveCity_EventScript_DraconidRivals_1); talking to LOCALID_LILYCOVE_MAY tries again and re-entering the map starts it again |
| 64 | NOTE | reentry | `data/scripts/draconid/act6.inc:215 DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift_2` | leg 6.10 DraconidVillage_PlayersHouse_1F_EventScript_DraconidMeteorAlert: gives control back before the scene is done (a choice at DraconidVillage_PlayersHouse_1F_EventScript_DraconidOfferLift); talking to LOCALID_DRACONID_HOUSE_ELDER tries again |
| 65 | NOTE | reentry | `data/scripts/draconid/act7.inc:178 SkyPillar_Outside_EventScript_DraconidDoubleBattle_2` | leg 7.06 SkyPillar_Outside_EventScript_DraconidTrialOfThree: gives control back before the scene is done (a choice at SkyPillar_Outside_EventScript_DraconidDoubleBattle); talking to LOCALID_SKY_PILLAR_OUTSIDE_ASTER tries again and re-entering the map starts it again |
| 66 | NOTE | reentry | `data/scripts/draconid/act7.inc:186 SkyPillar_Outside_EventScript_DraconidDoubleBattle_5` | leg 7.06 SkyPillar_Outside_EventScript_DraconidTrialOfThree: gives control back before the scene is done (a choice at SkyPillar_Outside_EventScript_DraconidDoubleBattle); talking to LOCALID_SKY_PILLAR_OUTSIDE_ASTER tries again and re-entering the map starts it again |
| 67 | NOTE | reentry | `data/scripts/draconid/act7.inc:310 SkyPillar_3F_EventScript_DraconidBattleZinnia_2` | leg 7.07 SkyPillar_3F_EventScript_DraconidZinniaScene: gives control back before the scene is done (a choice at SkyPillar_3F_EventScript_DraconidBattleZinnia); talking to LOCALID_SKY_PILLAR_3F_ZINNIA tries again and re-entering the map starts it again |
| 68 | NOTE | reentry | `data/scripts/draconid/act7.inc:752 SkyPillar_Top_EventScript_DraconidDeoxys_4` | leg P.15 SkyPillar_Top_EventScript_DraconidDeoxys: gives control back before the scene is done (a choice at SkyPillar_Top_EventScript_DraconidDeoxys); talking to LOCALID_SKY_PILLAR_TOP_DEOXYS tries again and re-entering the map starts it again |
| 69 | NOTE | reentry | `data/scripts/draconid/act7.inc:797 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_7` | leg P.04 LittlerootTown_ProfessorBirchsLab_EventScript_Rival: gives control back before the scene is done (a choice at LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameMay_5); talking to LOCALID_BIRCHS_LAB_RIVAL tries again and re-entering the map starts it again |
| 70 | NOTE | reentry | `data/scripts/draconid/act7.inc:820 LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_4` | leg P.05 LittlerootTown_ProfessorBirchsLab_EventScript_Brendan: gives control back before the scene is done (a choice at LittlerootTown_ProfessorBirchsLab_EventScript_DraconidPostgameBrendan_2); talking to LOCALID_BIRCHS_LAB_BRENDAN tries again and re-entering the map starts it again |
| 71 | NOTE | reentry | `data/scripts/draconid/act7.inc:914 DraconidVillage_Shrine_EventScript_Aster_2` | leg P.02 DraconidVillage_Shrine_EventScript_Aster: gives control back before the scene is done (a choice at DraconidVillage_Shrine_EventScript_Aster); talking to LOCALID_DRACONID_SHRINE_ASTER tries again and re-entering the map starts it again |
| 72 | NOTE | reentry | `data/scripts/draconid/act7.inc:940 DraconidVillage_EventScript_DraconidNerine_5` | leg P.01 DraconidVillage_EventScript_DraconidNerine: gives control back before the scene is done (a choice at DraconidVillage_EventScript_DraconidNerine); talking to LOCALID_DRACONID_VILLAGE_NERINE tries again and re-entering the map starts it again |
| 73 | NOTE | reentry | `data/scripts/draconid/act7x.inc:109 SkyPillar_Outside_EventScript_DraconidBattleWallace_2` | leg 7.05 SkyPillar_Outside_EventScript_DraconidWallaceScene: gives control back before the scene is done (a choice at SkyPillar_Outside_EventScript_DraconidBattleWallace); talking to LOCALID_SKY_PILLAR_WALLACE tries again and re-entering the map starts it again |
| 74 | NOTE | reentry | `data/scripts/draconid/act7x.inc:1316 MagmaHideout_4F_EventScript_DraconidGroudon` | leg 7x.01 MagmaHideout_4F_EventScript_DraconidGroudon: gives control back before the scene is done (a choice at MagmaHideout_4F_EventScript_DraconidGroudon); talking to LOCALID_MAGMA_HIDEOUT_4F_GROUDON_POSTGAME tries again and re-entering the map starts it again |
| 75 | NOTE | reentry | `data/scripts/draconid/act7x.inc:1364 SeafloorCavern_Room9_EventScript_DraconidKyogre` | leg 7x.02 SeafloorCavern_Room9_EventScript_DraconidKyogreSpot: gives control back before the scene is done (a choice at SeafloorCavern_Room9_EventScript_DraconidKyogre); talking to LOCALID_SEAFLOOR_CAVERN_KYOGRE_POSTGAME tries again and re-entering the map starts it again |
| 76 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse1 a lost battle: leg 7.12: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_BRENDAN starts it again; the way back is open |
| 77 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidPlayersHouse a lost battle: leg 7.11: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_MAY starts it again; the way back is open |
| 78 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse2 a lost battle: leg 7.10: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_WALLY starts it again; the way back is open |
| 79 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse2 a lost battle: leg 7.10: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_1 starts it again (or to LOCALID_DRACONID_VILLAGE_WALLY); the way back is open |
| 80 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse2 a lost battle: leg 7.10: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_2 starts it again (or to LOCALID_DRACONID_VILLAGE_WALLY); the way back is open |
| 81 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidPlayersHouse a lost battle: leg 7.11: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_3 starts it again (or to LOCALID_DRACONID_VILLAGE_MAY); the way back is open |
| 82 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidPlayersHouse a lost battle: leg 7.11: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_4 starts it again (or to LOCALID_DRACONID_VILLAGE_MAY); the way back is open |
| 83 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse1 a lost battle: leg 7.12: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_5 starts it again (or to LOCALID_DRACONID_VILLAGE_BRENDAN); the way back is open |
| 84 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidHouse1 a lost battle: leg 7.12: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_GRUNT_6 starts it again (or to LOCALID_DRACONID_VILLAGE_BRENDAN); the way back is open |
| 85 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidAster a lost battle: leg 7.13: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_ASTER starts it again; the way back is open |
| 86 | NOTE | reentry | `data/scripts/draconid/act7x.inc:25 Draconid_EventScript_VillageLost` | DraconidVillage_EventScript_DraconidFinalIntro a lost battle: leg 7.14: Draconid_EventScript_VillageLost sends the player to DraconidVillage_PlayersHouse_1F (8, 6); talking to LOCALID_DRACONID_VILLAGE_MAXIE fights again; the way back is open |
| 87 | NOTE | reentry | `data/scripts/draconid/act7x.inc:354 DraconidVillage_Shrine_EventScript_DraconidOfferLift_2` | leg 7.04 DraconidVillage_Shrine_EventScript_DraconidElderAfterRegidrago: gives control back before the scene is done (a choice at DraconidVillage_Shrine_EventScript_DraconidOfferLift); talking to LOCALID_DRACONID_SHRINE_ELDER tries again and re-entering the map starts it again |
| 88 | NOTE | reentry | `data/scripts/draconid/lance.inc:117 DraconidVillage_EventScript_LanceArrives_2` | leg P.02b DraconidVillage_EventScript_LanceArrives: gives control back before the scene is done (no choice); re-entering the map starts it again |
| 89 | NOTE | reentry | `data/scripts/draconid/lance.inc:137 DraconidVillage_EventScript_LanceSceneEnd` | leg P.02b DraconidVillage_EventScript_LanceArrives: gives control back before the scene is done (a choice at DraconidVillage_EventScript_LanceArrives, DraconidVillage_EventScript_LanceGifts); talking to LOCALID_DRACONID_VILLAGE_LANCE tries again |
| 90 | NOTE | reentry | `data/scripts/draconid/lance.inc:137 DraconidVillage_EventScript_LanceSceneEnd` | leg P.02b DraconidVillage_EventScript_LanceArrives: gives control back before the scene is done (a choice at DraconidVillage_EventScript_LanceArrives); talking to LOCALID_DRACONID_VILLAGE_LANCE tries again |
| 91 | NOTE | trap | `progression.json leg 2.07` | a warp to Route104 (13, 51): a heal location reached in 11 steps |
| 92 | NOTE | trap | `progression.json leg 2.10` | a warp to Route104_MrBrineysHouse (5, 4): a heal location reached in 12 steps |
| 93 | NOTE | trap | `progression.json leg 5.04` | a warp to MossdeepCity_SpaceCenter_1F (13, 1): the next scene reached in 13 steps |
| 94 | NOTE | trap | `progression.json leg 7.10` | a warp to DraconidVillage_PlayersHouse_1F (8, 6): a heal location reached in 0 steps |
| 95 | NOTE | trap | `progression.json leg 7.11` | a warp to DraconidVillage_PlayersHouse_1F (8, 6): a heal location reached in 0 steps |
| 96 | NOTE | trap | `progression.json leg 7.12` | a warp to DraconidVillage_PlayersHouse_1F (8, 6): a heal location reached in 0 steps |
| 97 | NOTE | trap | `progression.json leg 7.13` | a warp to DraconidVillage_PlayersHouse_1F (8, 6): a heal location reached in 0 steps |
| 98 | NOTE | trap | `progression.json leg 7.14` | a warp to DraconidVillage_PlayersHouse_1F (8, 6): a heal location reached in 0 steps |
| 99 | NOTE | trap | `progression.json leg P.09` | a warp to SouthernIsland_Exterior (13, 22): a heal location reached in 0 steps |
| 100 | NOTE | trap | `progression.json leg P.09` | a warp to NavelRock_Harbor (8, 4): a heal location reached in 2 steps |
| 101 | NOTE | trap | `progression.json leg P.09` | a warp to BirthIsland_Harbor (8, 4): a heal location reached in 2 steps |
| 102 | NOTE | trap | `progression.json leg P.09` | a warp to FarawayIsland_Entrance (13, 38): a heal location reached in 2 steps |
| 103 | NOTE | trap | `progression.json leg P.09` | a warp to SSTidalCorridor (1, 10): no heal location from there - by design: the SS Tidal: the crossing (C: the step counter, or the cabin bed) lands the player in Lilycove or Slateport |
| 104 | NOTE | trap | `progression.json leg P.14` | a warp to LilycoveCity_Harbor (8, 11): a heal location reached in 1 steps |
| 105 | NOTE | trap | `progression.json leg P.20` | a warp to EverGrandeCity_HallOfFame (7, 16): no heal location from there - by design: the Hall of Fame scene sends the player home |
