#pragma once
#include "MoveRandEnemy.h"

class Slime : public MoveRandEnemy
{
public:
	Slime(string n);
	~Slime();

	char getChar(void);
};

