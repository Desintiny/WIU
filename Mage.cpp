#include "Mage.h"

Mage::Mage(string n) : Player(n)
{
	setHealth(24);
	setAttack(10);
	setStamina(20);
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
