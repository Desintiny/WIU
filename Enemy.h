#pragma once
#include "Entity.h"

class Enemy : public Entity
{

public:
	Enemy(string n);
	~Enemy();

	void EnemyMovement(char mapGrid[12][12]);

	virtual void EnemyAttack();
};