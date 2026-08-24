#pragma once
#include "Player.h"

class Mage : public Player
{
public:
	Mage(string n);
	~Mage();

	void EquipWeapon();
};

