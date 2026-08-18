#pragma once
#include "Entity.h"
// #include "Weapon.h"

class Player : public Entity
{
	char moveBtn[4];
	char intDirection[4];

	// Weapon* playerWeapon;

protected:
	char GetDirection(int i);

public:
	Player(string n);
	~Player();

	void PlayerMovement();
	virtual void PlayerAttack();
	virtual void EquipWeapon();
};

