#include "Mage.h"

Mage::Mage(string n) : Player(n)
{
	setHealth(24);
	setMaxHealth(24);
	
	setStamina(10);
	setMaxStamina(10);

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
