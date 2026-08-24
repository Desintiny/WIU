#include "ValArcher.h"

ValArcher::ValArcher(string n) : Enemy(n)
{
	setHealth(16);
	setMaxHealth(16);
	setAttack(4);
}

ValArcher::~ValArcher()
{

}

void ValArcher::EnemyMovement(Entity* target, char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

	int rowDist = abs(target->getRow() - getRow());
	int colDist = abs(target->getCol() - getCol());

	if (rowDist + colDist <= 1)
	{
		if (target->getRow() < getRow()) // UP
		{
			newRow++;
		}
		else if (target->getCol() < getCol()) // LEFT
		{
			newCol++;
		}
		else if (target->getRow() > getRow()) // DOWN
		{
			newRow--;
		}
		else if (target->getCol() > getCol()) // RIGHT
		{
			newCol--;
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

	if (newRow >= 1 && newRow <= 10 && // within the border
		newCol >= 1 && newCol <= 10 && // within the border
		mapGrid[newRow][newCol] == '.') // if the next new position is '.'
	{
		mapGrid[getRow()][getCol()] = '.';

		setRow(newRow);
		setCol(newCol);

		mapGrid[getRow()][getCol()] = 'A';
	}
}