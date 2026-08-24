#pragma once
#include "MoveTargEnemy.h"

class ValSwordman : public MoveTargEnemy
{
public:
	ValSwordman(string n);
	~ValSwordman();

	char getChar(void);
};

