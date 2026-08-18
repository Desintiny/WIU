#pragma once
#include "Player.h"

class Archer : public Player
{
public:
	Archer(string n);
	~Archer();

	void PlayerAttack();
	void EquipWeapon();
};

