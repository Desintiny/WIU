#include "Goblin.h"

Goblin::Goblin(string n) : MoveTargEnemy(n)
{
	setHealth(18);
	setMaxHealth(18);
	setAttack(5);
};

Goblin::~Goblin()
{

};

char Goblin::getChar()
{
	return 'G';
}
