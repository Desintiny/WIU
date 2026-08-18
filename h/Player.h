#pragma once
#include "Entity.h"

class Player : public Entity
{
	char intDirection[4];

protected:
	char GetDirection(int i);

public:
	Player(string n);
	~Player();

	void PlayerMovement(char input, char mapGrid[12][12]);
	virtual void PlayerAttack();
	virtual void EquipWeapon();
};
