#include "global.h"
#include "item.h"
#include "test/test.h"

// Draconid Emerald (D-320, D-322): the battle item counter sells every Mega Stone and Z-Crystal after the
// Champion, so each has a price (a 0-price item would be free in a mart); shops never buy one back.

static bool32 IsMegaStoneOrZCrystal(enum Item item)
{
    enum HoldEffect holdEffect = GetItemHoldEffect(item);
    return holdEffect == HOLD_EFFECT_MEGA_STONE || holdEffect == HOLD_EFFECT_Z_CRYSTAL;
}

TEST("Every Mega Stone and Z-Crystal has a price")
{
    u32 item, count = 0;

    for (item = ITEM_NONE + 1; item < ITEMS_COUNT; item++)
    {
        if (!IsMegaStoneOrZCrystal(item))
            continue;
        count++;
        EXPECT_NE(GetItemPrice(item), 0);
    }
    EXPECT_NE(count, 0);
}

TEST("Shops don't buy Mega Stones and Z-Crystals back")
{
    u32 item;

    ASSUME(I_SELL_MEGA_STONES_Z_CRYSTALS == FALSE);
    for (item = ITEM_NONE + 1; item < ITEMS_COUNT; item++)
    {
        if (IsMegaStoneOrZCrystal(item))
            EXPECT_EQ(GetItemSellPrice(item), 0);
    }
}

TEST("Other held items still sell for their share of the price")
{
    ASSUME(GetItemPrice(ITEM_LEFTOVERS) != 0);
    EXPECT_EQ(GetItemSellPrice(ITEM_LEFTOVERS), GetItemPrice(ITEM_LEFTOVERS) / ITEM_SELL_FACTOR);
}
