#pragma once
#include "Player.h"

class Berserker : public Player
{
public:
	Berserker(string n);
	~Berserker();

	void PlayerAttack();
	void EquipWeapon();
};

