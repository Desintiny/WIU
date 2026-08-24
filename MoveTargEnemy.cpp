#include "MoveTargEnemy.h"

MoveTargEnemy::MoveTargEnemy(string n) : Enemy(n)
{

};

MoveTargEnemy::~MoveTargEnemy()
{

};

void MoveTargEnemy::EnemyMovement(Entity* target, char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

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

	if (newRow >= 1 && newRow <= 10 && // within the border
		newCol >= 1 && newCol <= 10 && // within the border
		mapGrid[newRow][newCol] == '.') // if the next new position is '.'
	{
		mapGrid[getRow()][getCol()] = '.';

		setRow(newRow);
		setCol(newCol);

		mapGrid[getRow()][getCol()] = getChar();
	}
}

char MoveTargEnemy::getChar()
{
	return 'E';
}