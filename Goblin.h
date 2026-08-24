#pragma once
#include "MoveTargEnemy.h"

class Goblin : public MoveTargEnemy
{
public:
	Goblin(string n);
	~Goblin();

	char getChar(void);
};

