#include "Berserker.h"

Berserker::Berserker(string n) : Player(n)
{
	setHealth(40);
	setAttack(8);
	setStamina(10);
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