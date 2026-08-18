#include "Player.h"
#include <iostream>

Player::Player(string n) : Entity(n)
{
	intDirection[0] = 'i';
	intDirection[1] = 'j';
	intDirection[2] = 'k';
	intDirection[3] = 'l';

	minRange = 0;
	maxRange = 0;
}

Player::~Player()
{
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

void Player::PlayerAtkDirection(char input, char mapGrid[12][12])
{
	int newRow = getRow();
	int newCol = getCol();

	if (input == 'i' || input == 'I') // UP
	{
		newRow--;
	}
	else if (input == 'j' || input == 'J') // LEFT
	{
		newCol--;
	}
	else if (input == 'k' || input == 'K') // RIGHT
	{
		newRow++;
	}
	else if (input == 'l' || input == 'L') // DOWN
	{
		newCol++;
	}
	else
	{
		return;
	}

	std::cout << "player is attacking at row: " << newRow << " and col: " << newCol << endl;
}

void Player::PlayerAttack()
{
}

void Player::EquipWeapon()
{
}

void Player::setMinRange(int r)
{
	minRange = r;
}

int Player::getMinRange(void)
{
	return minRange;
}

void Player::setMaxRange(int r)
{
	maxRange = r;
}

int Player::getMaxRange(void)
{
	return maxRange;
}