#include "Berserker.h"

Berserker::Berserker(string n) : Player(n)
{
    static const int health = 40;
    static const int stamina = 10;
    static const int dodge = 5;

    setHealth(health);
    setMaxHealth(health);

    setStamina(stamina);
    setMaxStamina(stamina);

    setAttack(8);

    setMinRange(1);
    setMaxRange(1);

    setDodgeChance(dodge);
}

Berserker::~Berserker()
{

}

void Berserker::EquipWeapon()
{

}
void Berserker::EquipWeapon()
{

}
