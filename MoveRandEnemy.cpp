#include "MoveRandEnemy.h"

MoveRandEnemy::MoveRandEnemy(string n) : Enemy(n)
{

};

MoveRandEnemy::~MoveRandEnemy()
{

};

void MoveRandEnemy::EnemyMovement(Entity* target, char mapGrid[12][12])
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

char MoveRandEnemy::getChar()
{
	return 'E';
}