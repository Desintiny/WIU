#pragma once
#include "Enemy.h"

class ValArcher : public Enemy
{
public:
	ValArcher(string n);
	~ValArcher();

	void EnemyMovement(Entity* target, char mapGrid[12][12]);
};

