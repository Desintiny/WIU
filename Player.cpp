#include "Player.h"
#include <iostream>

Player::Player(string n) : Entity(n)
{
	staminaPts = 0;
	maxStaminaPts = 0;

	minRange = 0;
	maxRange = 0;
}

Player::~Player()
{
}

void Player::PlayerMovement(char sym, char input, char mapGrid[12][12])
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

		mapGrid[getRow()][getCol()] = sym;
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
	else if (input == 'i' || input == 'I')
	{
		inventory.displayInventory();
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

void Player::setStamina(int s)
{
	staminaPts = s;
}

int Player::getStamina(void)
{
	return staminaPts;
}

void Player::setMaxStamina(int s)
{
	maxStaminaPts = s;
}

int Player::getMaxStamina(void)
{
	return maxStaminaPts;
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