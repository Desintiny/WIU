#pragma once
#include "Enemy.h"

class MoveTargEnemy : public Enemy
{
public:
	MoveTargEnemy(string n);
	~MoveTargEnemy();

	void EnemyMovement(Entity* target, char mapGrid[12][12]);

	virtual char getChar(void);
};