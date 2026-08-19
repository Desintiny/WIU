#include "Mage.h"

Mage::Mage(string n) : Player(n)
{
	static const int health = 24;
	static const int stamina = 10;

	setHealth(health);
	setMaxHealth(health);

	setStamina(stamina);
	setMaxStamina(stamina);

	setAttack(10);

	setMinRange(2);
	setMaxRange(3);
};

Mage::~Mage()
{

}

void Mage::PlayerAttack()
{

}

void Mage::EquipWeapon()
{

}
