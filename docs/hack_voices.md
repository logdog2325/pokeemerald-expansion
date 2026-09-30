# Draconid Emerald – voice sheet: Maxie, Brendan, May

How the three story characters the playtester singled out talk (feedback 1.26: "make sure Maxie talks like he
does in game with his tone of voice and mannerisms. Same with Brendan and May, I don't want them clunky or AI
sounding dialogue, it should be smooth"). Read this before writing a line for any of them. The rules are
decisions D-210 – D-212 in [hack_decisions.md](hack_decisions.md); the lines as they stand are in
[hack_script.md](hack_script.md). Reference lines are vanilla Emerald, quoted from the `master` branch
(`git show master:data/maps/<Map>/scripts.inc`).

## Rules for all three
- **One idea per text box, 1–3 boxes a beat.** A scene is a conversation, not a speech. If a box needs a third
  line, it had better be one sentence.
- **No written-sounding tricks**: no "Not X. Y." / "It's not X, it's Y" / "X, not Y" antitheses; no rhetorical
  triplets ("Land for people. For POKéMON. For children like you."); no stacked fragments for drama ("Twice."
  "Every single time."); no em dashes (a cut-off line ends in "…"); at most one "…" per box.
- **Nobody narrates their own feelings** ("That's what makes it worse", "I find I'm only tired"). They react:
  "Tch…", "What?!", "Man, you're strong."
- **Emerald's register**: short, plain words; names and places in CAPS as vanilla does (TEAM MAGMA, the LAB,
  MT. CHIMNEY); family words in lower case in the rivals' mouths ("my dad", "Dad"), as vanilla writes them.
  No modern slang or idioms.
- **Keep what the line does**: story facts, names, where the player is sent (Maxie's calls always name the next
  place), `{PLAYER}` uses, and the arc – Brendan feels betrayed, May half-suspects the player is secretly good
  (a crack, not warmth, until the turn), Maxie is believable and even likable, so the betrayal costs something.
- **Wrap by hand where it matters**: `format()` fills lines greedily; a `\n` in the string keeps a name on one
  line ("MT. CHIMNEY") and avoids a one-word last line.

## Brendan and May while the player wears red
From Rustboro to the Sootopolis turn (`REPUTATION_UNIFORM`) the rivals don't know the player's mission, so they
treat them as an **enemy of HOENN**: they want to stop TEAM MAGMA and protect people, and they are angry the
player joined. Their lines before and after every battle in Acts 1–5 are hostile and earnest, not friendly
banter (the playtester: "have them be really hostile to you because they're trying to stop Team Magma and protect
Hoenn, not knowing your true mission").
- **Brendan**: betrayed and angry. "Those guys want to wreck HOENN!", "Then I'll stop you myself!", "If MAY's
  wrong about you, I'm the one who stops you."
- **May**: fights just as hard. Her suspicion that there is more to it shows only as a **small crack** – a
  hesitation or one question per scene ("…What are you really doing, {PLAYER}?", "…So why are you wearing that
  uniform?") – never as warmth. Even when she covers for the player at the Weather Institute she closes the door
  again: "But don't think this changes anything. You still work for MAGMA."
- Things they hand over (the Dowsing Machine, Go-Goggles, HM Fly) come grudgingly ("The winner gets this.
  That's the rule, even for MAGMA."); the PokéNav registrations are to keep tabs on a MAGMA grunt.
- **After the turn** (Sootopolis and later) they warm up as the story says: May's "I KNEW it!" and Brendan's
  awkward apology are saved for then.

## Maxie
**How he talks.** Composed and formal. Full sentences, few contractions ("I will", "It is"). Grandiose about
the land, humankind and "our ideal", and sincere about it: he believes he is saving people. Calm menace; dry,
intellectual pride ("That is the difference between us"). When something goes wrong he gets **short and sharp**
("What?!", "Enough.") and then recovers his composure. He praises the player sparingly and precisely, which is
why it lands. Laughs "Fufufu…" when pleased, "Fuhahaha…" when broken; "Humph" when displeased.

Reference lines (vanilla Emerald):
- "Now you listen. Long ago, living things used the land to live and grow. That is why land is all important!
  It is the cradle of all!" (Mt. Chimney)
- "It is for further advancement of humankind and POKéMON!" (Mt. Chimney)
- "Oh! There was no need for you to learn that much. But, no matter!" (Mt. Chimney)
- "What?! I, MAXIE, was caught off guard?!" (Mt. Chimney, defeat)
- "Fufufu… Even without the METEORITE, if we obtain that ORB… Fufufu…" (Mt. Chimney)
- "Humph… You think I didn't know that?" (Magma Hideout)
- "MAXIE: This defies belief… Those super-ancient POKéMON… Their power is unbelievable." (Route 128)
- "After all our fruitless scheming and frantic efforts, that one POKéMON's simple action puts everything right
  again as if nothing had happened… Fu… Fuhahaha…" (Sootopolis)

Use: "humankind and POKéMON", "the land", "our ideal", "No matter.", "Fufufu…", "Humph", "is it not?",
"I leave it in your hands", "I will remember this", orders as plain imperatives ("Guard the path below us.").
Avoid: slang and casual fillers ("okay", "kid", "guys"); gushing ("amazing!"); strings of exclamation marks
outside anger; an aphorism in every scene (one per scene at most: "Every great work begins with a small stone");
explaining his plan in more than two or three boxes at a time.

## Brendan
**How he talks.** Casual, confident, competitive. Short sentences, a bit brash, but good-hearted underneath.
Opens with "Huh?", "Hmm…", "Hey"; sizes the player up; settles things with a battle. In this story he feels
betrayed: while the player wears red that comes out as anger and bluntness ("Why would someone like you join
THEM?"), never as a speech about his feelings. After the turn he gets awkward and brief ("Don't make me say that
twice.").

Reference lines (vanilla Emerald):
- "Huh, {PLAYER}, you're not too shabby." (Route 103)
- "…Oh, yeah, Dad gave you a POKéMON." (Route 103)
- "Hmm… You're pretty good." (Rustboro, Route 110)
- "Let me see how good you got. I'll test you! Now! It's a battle, so battle!" (Route 119)
- "Hmm… You've gotten pretty darn decent." (Route 119)
- "I'm running an errand for my dad. No, I'm not buying any DOLLS." (Lilycove)
- "Aww, but you know I'm not going to lose to no {PLAYER}." (Lilycove)
- "Whaaaat?! … It can't be helped if that's the rule. {PLAYER}, way to go! Congratulations!" (Champion's room)

Use: "Huh?", "Hmm…", "Tch…", "Man,", "Come on!", "Forget it!", "my dad", "okay?", "Let's battle!",
"Don't you dare…". Avoid: poetic or reflective lines ("You were always going to be strong"), therapy words, long
sentences, more than one question per box, sulking fragments.

## May
**How she talks.** Warm, upbeat, curious, quick to cheer (with friends: before the uniform and after the turn).
Says what she thinks, teases a little, gets excited ("Wow!", "Yikes!", "Eheheh!"). A researcher's eye: she
notices how POKéMON act around their trainer ("But yours trust you."), which is where her doubt about the
player starts. While the player wears red she is blunt and determined to stop MAGMA; the doubt is a crack, not
a smile. She is the loudest when she is proved right ("I KNEW it!", Sootopolis).

Reference lines (vanilla Emerald):
- "Wow! That's great! {PLAYER}{KUN}, you're pretty good!" (Route 103)
- "Yikes! You're better than I expected!" (Rustboro, Route 110)
- "MAY: {PLAYER}{KUN}! Where were you? I was looking for you!" (Route 119)
- "Ready with your POKéMON? Of course you are! Go!" (Route 119)
- "Achah! {PLAYER}{KUN}, you're strong!" (Route 119)
- "I bought a whole bunch of DOLLS and POSTERS." (Lilycove)
- "Groan… … I'm just joking! That's okay! That's the rule!" (Champion's room)
- "I… I have this dream of becoming friends with POKéMON all over the world." (her bedroom)

Use: "Oh!", "Wow!", "Hehe!", "Forget it.", "my dad", notes about POKéMON and trust, exclamation marks;
in uniform scenes plain, direct challenges ("I'm going to stop you right here!"). Avoid: cheerful banter with a
MAGMA grunt, winks and "I told you so" before the turn, brooding or cryptic menace, fragments for effect,
anything that sounds older than she is.
