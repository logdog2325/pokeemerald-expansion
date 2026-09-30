#ifndef GUARD_CONSTANTS_DRACONID_H
#define GUARD_CONSTANTS_DRACONID_H

// Draconid Emerald story constants. See docs/hack_changes.md.

// VAR_DRACONID_STATE: progress through the opening in Draconid Village
#define DRACONID_STATE_NEW_GAME        0 // waking up in the bedroom
#define DRACONID_STATE_SET_CLOCK       1 // Mom asked the player to set the clock
#define DRACONID_STATE_CLOCK_SET       2 // go to the Elder's house
#define DRACONID_STATE_EGG_RECEIVED    3 // egg chosen, hatching rite at the shrine
#define DRACONID_STATE_EGG_HATCHED     4 // hatched; Mom waits outside the shrine
#define DRACONID_STATE_READY_TO_LEAVE  5 // got the Running Shoes, may leave the village
#define DRACONID_STATE_LEFT_VILLAGE    6 // met Aster on Draconid Pass

// VAR_STARTER_MON / VAR_ASTER_EGG: the three Draconid eggs (order of the Elder's choice)
#define DRACONID_EGG_DEINO             0
#define DRACONID_EGG_DREEPY            1
#define DRACONID_EGG_JANGMO_O          2
#define DRACONID_EGG_COUNT             3

#define DRACONID_EGG_SPECIES_0         SPECIES_DEINO
#define DRACONID_EGG_SPECIES_1         SPECIES_DREEPY
#define DRACONID_EGG_SPECIES_2         SPECIES_JANGMO_O

// Level the hatchling is raised to after the rite (eggs hatch at EGG_HATCH_LEVEL = 1)
#define DRACONID_HATCHLING_LEVEL       5

// VAR_SECOND_STARTER: Prof. Birch's gift after the first Gym
#define SECOND_STARTER_NONE            0
#define SECOND_STARTER_CHARMANDER      1
#define SECOND_STARTER_TOTODILE        2
#define SECOND_STARTER_TREECKO         3

#endif // GUARD_CONSTANTS_DRACONID_H
