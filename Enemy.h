#pragma once
#include "Entity.h"

#include <cstdlib>
#include <iostream>
using namespace std;

class Enemy : public Entity
{
private:
	bool recovering;
	int disabledTurns;

public:
	Enemy(string n);
	~Enemy();

	virtual void EnemyMovement(Entity* target, char mapGrid[12][12]) = 0;
	virtual void EnemyAttack(Entity* target);

	bool getRecovering();
	void setRecovering(bool value);

	int GetDisabledTurns();
	void SetDisabledTurns(int turns);
};
