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

	switch (dir)
	{
		case 1: newRow--;
		case 2:newCol--;
		case 3:newRow++;
		case 4:newCol++;
		default: return;
	}

	if (newRow >= 1 && newRow <= 10 &&
		newCol >= 1 && newCol <= 10 &&
		mapGrid[newRow][newCol] == '.')
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