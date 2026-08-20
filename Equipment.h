#pragma once
#pragma once

class Equipment
{
private:
    int Accuracy;
    int Health;
    int Damage;

public:
    Equipment();

    int GetAccuracy();
    int GetHealth();
    int GetDamage();

    void AddAccuracy(int accuracy);
    void AddHealth(int health);
    void AddDamage(int damage);
};
