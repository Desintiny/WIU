#include "Slime.h"

Slime::Slime (string n) : MoveRandEnemy(n)
{
	setHealth(12);
	setMaxHealth(12);
	setAttack(3);
};

Slime::~Slime()
{

};

char Slime::getChar()
{
	return 'S';
}