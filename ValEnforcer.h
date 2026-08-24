#pragma once
#include "MoveRandEnemy.h"

class ValEnforcer : public MoveRandEnemy
{
public:
	ValEnforcer(string n);
	~ValEnforcer();

	char getChar(void);
};

