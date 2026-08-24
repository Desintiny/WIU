#pragma once
#include "Enemy.h"

class WildBoar : public Enemy
{
public:
	WildBoar(string n);
	~WildBoar();

	void EnemyMovement(Entity* target, char mapGrid[12][12]);

	void EnemyAttack(Entity* target);
};

