#pragma once
#include "Entity.h"

class Player : public Entity
{
	int staminaPts, maxStaminaPts;

	int minRange;
	int maxRange;

public:
	Player(string n);
	~Player();

	void PlayerMovement(char sym, char input, char mapGrid[12][12]);
	bool PlayerAtkDirection(char input, int& dirRow, int& dirCol);

	virtual void PlayerAttack(Entity* enemy);
	virtual void EquipWeapon();

	void setStamina(int);
	int getStamina(void);

	void setMaxStamina(int);
	int getMaxStamina(void);

	void setMinRange(int);
	int getMinRange(void);

	void setMaxRange(int);
	int getMaxRange(void);

	//Test code
	bool PlayerAbilityDirection(char input, int& targetRow, int& targetCol);
};
