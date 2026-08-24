#include "Equipment.h"

Equipment::Equipment() {
    Accuracy = 0;
    CritChance = 0;
    Health = 0;
    Damage = 0;
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
