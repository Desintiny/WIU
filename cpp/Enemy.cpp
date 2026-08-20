#include "Enemy.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Enemy::Enemy(string n) : Entity(n)
{
	// baseline stats so enemies aren't a 1-hit kill (Entity defaults everything to 0 otherwise)
	setHealth(18);
	setMaxHealth(18);
	setAttack(5);
}

Enemy::~Enemy()
{

}

void Enemy::EnemyMovement(char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

	int dir = rand() % 4 + 1;

	if (dir == 1) // UP
	{
		newRow--;
	}
	else if (dir == 2) // LEFT
	{
		newCol--;
	}
	else if (dir == 3) // RIGHT
	{
		newRow++;
	}
	else if (dir == 4) // DOWN
	{
		newCol++;
	}
	else
	{
		return;
	}

	if (newRow >= 1 && newRow <= 10 && // within the border
		newCol >= 1 && newCol <= 10 && // within the border
		mapGrid[newRow][newCol] == '.') // if the next new position is '.'
	{
		mapGrid[getRow()][getCol()] = '.';

		setRow(newRow);
		setCol(newCol);

		mapGrid[getRow()][getCol()] = 'E';
	}
}

void Enemy::EnemyAttack(Entity* target)
{
	if (target != nullptr)
	{
		int dmg = getAttack();

		target->TakeDamage(dmg);

		cout << getName() << " attacks " << target->getName()
			 << " for " << dmg << " damage!" << endl;

		if (!target->IsAlive())
		{
			cout << target->getName() << " has been defeated!" << endl;
		}
		else
		{
			cout << target->getName() << " has "
				 << target->getHealth() << " HP left." << endl;
		}
	}
}
