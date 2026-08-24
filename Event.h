#pragma once
#include <vector>
#include "Player.h"

class Event
{
private:
    std::vector<int> usedEvents;

    bool IsUsed(int event);

public:
    void PathChoice(Player* player);
    void ForestEvent(int event, Player* player);

    // Heal helpers
    void HealToMax(Player* player);
    void Heal20(Player* player);
};
