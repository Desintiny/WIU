#pragma once

class Equipment
{
private:
    int Accuracy;
    int CritChance;
    int Health;
    int Damage;

public:
    Equipment();

    int GetAccuracy();
    int GetHealth();
    int GetDamage();
    int GetCritChance();

    void AddAccuracy(int accuracy);
    void AddCritChance(int critchance);
    void AddHealth(int health);
    void AddDamage(int damage);
};
