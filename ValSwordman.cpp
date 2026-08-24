#include "ValSwordman.h"

ValSwordman::ValSwordman (string n) : MoveTargEnemy(n)
{
	setHealth(22);
	setMaxHealth(22);
	setAttack(6);
}

ValSwordman::~ValSwordman()
{

}

char ValSwordman::getChar()
{
	return 'S';
}