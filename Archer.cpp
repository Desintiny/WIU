#include "Archer.h"

Archer::Archer(string n) : Player(n)
{
	setHealth(28);
	setAttack(7);
	setStamina(10);
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