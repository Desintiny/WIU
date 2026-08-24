#include "WildBoar.h"
#include <iostream>

WildBoar::WildBoar(string n) : Enemy(n)
{
	setHealth(24);
	setMaxHealth(24);
	setAttack(8);
}

WildBoar::~WildBoar()
{

}

void WildBoar::EnemyMovement(Entity* target, char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

	if (getHealth() >= 24)
	{
		int dir = rand() % 4 + 1;

		if (dir == 1) // UP
		{
			newRow--;
		}
		else if (dir == 2) // LEFT
		{
			newCol--;
		}
		else if (dir == 3) // DOWN
		{
			newRow++;
		}
		else if (dir == 4) // RIGHT
		{
			newCol++;
		}
		else
		{
			return;
		}
	}
	else
	{
		if (target->getRow() < getRow()) // UP
		{
			newRow--;
		}
		else if (target->getCol() < getCol()) // LEFT
		{
			newCol--;
		}
		else if (target->getRow() > getRow()) // DOWN
		{
			newRow++;
		}
		else if (target->getCol() > getCol()) // RIGHT
		{
			newCol++;
		}
		else
		{
			return;
		}
	}


	if (newRow >= 1 && newRow <= 10 &&
		newCol >= 1 && newCol <= 10 &&
		mapGrid[newRow][newCol] == '.')
	{
		mapGrid[getRow()][getCol()] = '.';

		setRow(newRow);
		setCol(newCol);

		mapGrid[getRow()][getCol()] = 'W';
	}
}

void WildBoar::EnemyAttack(Entity* target)
{
	if (getHealth() < 24)
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
}