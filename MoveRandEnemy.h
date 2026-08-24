#pragma once
#include "Enemy.h"

class MoveRandEnemy : public Enemy
{
public:
	MoveRandEnemy(string n);
	~MoveRandEnemy();

	void EnemyMovement(Entity* target, char mapGrid[12][12]);

	virtual char getChar(void);
};