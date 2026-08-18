#include "Player.h"

Player::Player(string n) : Entity(n)
{
	intDirection[0] = 'i';
	intDirection[1] = 'j';
	intDirection[2] = 'k';
	intDirection[3] = 'l';
}

Player::~Player()
{
}

char Player::GetDirection(int i)
{
	return intDirection[i];
}

void Player::PlayerMovement(char input, char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

	if (input == 'w' || input == 'W') // UP
	{
		newRow--;
	}
	else if (input == 'a' || input == 'A') // LEFT
	{
		newCol--;
	}
	else if (input == 's' || input == 'S') // RIGHT
	{
		newRow++;
	}
	else if (input == 'd' || input == 'D') // DOWN
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

		mapGrid[getRow()][getCol()] = 'P';
	}
}

void Player::PlayerAttack()
{
}

void Player::EquipWeapon()
{
}
