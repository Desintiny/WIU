#pragma once
#include <vector>

class Event
{
private:
    std::vector<int> usedEvents;
    bool IsUsed(int event);

public:
    void PathChoice();
    void ForestEvent(int event);
};