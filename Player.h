#pragma once
#include "Entity.h"

class Player : public Entity
{
	char intDirection[4];
	int minRange;
	int maxRange;

public:
	Player(string n);
	~Player();

	void PlayerMovement(char input, char mapGrid[12][12]);
	void PlayerAtkDirection(char input, char mapGrid[12][12]);

	virtual void PlayerAttack();
	virtual void EquipWeapon();

	void setMinRange(int);
	int getMinRange(void);

	void setMaxRange(int);
	int getMaxRange(void);
};
