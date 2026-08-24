#include "ValEnforcer.h"

ValEnforcer::ValEnforcer(string n) : MoveRandEnemy(n)
{
	setHealth(28);
	setMaxHealth(28);
	setAttack(8);
}

ValEnforcer::~ValEnforcer()
{

}

char ValEnforcer::getChar()
{
	return 'E';
}