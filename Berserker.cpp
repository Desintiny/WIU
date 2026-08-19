#include "Berserker.h"

Berserker::Berserker(string n) : Player(n)
{
	setHealth(40);
	setMaxHealth(40);

	setStamina(10);
	setMaxStamina(10);

	setAttack(8);
	
	setMinRange(1);
	setMaxRange(1);
};

Berserker::~Berserker()
{

}

void Berserker::PlayerAttack()
{

}

void Berserker::EquipWeapon()
{

}