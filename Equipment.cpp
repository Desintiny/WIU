#include "Equipment.h"

Equipment::Equipment() {
    Accuracy = 0;
    CritChance = 0;
    Health = 0;
    Damage = 0;
    ThornsChance = 0;
    DisableTurns = 0;
}

int Equipment::GetAccuracy() {
    return Accuracy;
}

int Equipment::GetHealth() {
    return Health;
}

int Equipment::GetDamage() {
    return Damage;
}

int Equipment::GetCritChance() {
    return CritChance;
}

void Equipment::AddAccuracy(int accuracy) {
    Accuracy += accuracy;
}

void Equipment::AddHealth(int health) {
    Health += health;
}

void Equipment::AddDamage(int damage) {
    Damage += damage;
}
void Equipment::AddCritChance(int critChance)
{
    CritChance += critChance;
}
void Equipment::AddThornsChance(int chance)
{
    ThornsChance += chance;
}

int Equipment::GetThornsChance()
{
    return ThornsChance;
}

int Equipment::GetDisableTurns()
{
    return DisableTurns;
}

void Equipment::AddDisableTurns(int turns)
{
    DisableTurns += turns;
}
