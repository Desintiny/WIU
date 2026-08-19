#include "Berserker.h"

Berserker::Berserker(string n) : Player(n)
{
	static const int health = 40;
	static const int stamina = 10;

	setHealth(health);
	setMaxHealth(health);

	setStamina(stamina);
	setMaxStamina(stamina);

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