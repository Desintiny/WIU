#pragma once

class Equipment
{
private:
    int Accuracy;
    int CritChance;
    int Health;
    int Damage;
    int ThornsChance;
    int DisableTurns;

public:
    Equipment();

    int GetAccuracy();
    int GetHealth();
    int GetDamage();
    int GetCritChance();
    int GetThornsChance();

    void AddAccuracy(int accuracy);
    void AddCritChance(int critchance);
    void AddHealth(int health);
    void AddDamage(int damage);
    void AddThornsChance(int chance);

    int GetDisableTurns();
    void AddDisableTurns(int turns);
};
