#include "Mage.h"

Mage::Mage(string n) : Player(n)
{
    static const int health = 24;
    static const int stamina = 10;
    static const int dodge = 3;

    setHealth(health);
    setMaxHealth(health);

    setStamina(stamina);
    setMaxStamina(stamina);

    setAttack(10);

    setMinRange(1);
    setMaxRange(3);

    setDodgeChance(dodge);
}

Mage::~Mage()
{

}

void Mage::EquipWeapon()
{

}
