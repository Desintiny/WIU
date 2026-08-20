#include "Archer.h"

Archer::Archer(string n) : Player(n)
{
	static const int health = 28;
	static const int stamina = 10;

	setHealth(health);
	setMaxHealth(health);
	
	setStamina(stamina);
	setMaxStamina(stamina);

	setAttack(7);

	setMinRange(1);
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
