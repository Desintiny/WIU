#include "Archer.h"

Archer::Archer(string n) : Player(n)
{
	setHealth(28);
	setMaxHealth(28);
	
	setStamina(10);
	setMaxStamina(10);

	setAttack(7);

	setMinRange(3);
	setMaxRange(4);
};

Archer::~Archer()
{

}

void Archer::PlayerAttack()
{

}

void Archer::EquipWeapon()
{

}