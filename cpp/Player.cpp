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
		mapGrid[newRow][newCol] == '.' || mapGrid[newRow][newCol] == 'X')
	{
		mapGrid[getRow()][getCol()] = '.';

		setRow(newRow);
		setCol(newCol);

		mapGrid[getRow()][getCol()] = sym;
	}
}

// Returns the DIRECTION of the attack (-1, 0, or 1 on each axis), not a fixed target tile.
// Game.cpp uses this direction to scan from minRange to maxRange along that line,
// so ranged classes (Archer/Mage) can actually hit further away than 1 tile.
bool Player::PlayerAtkDirection(char input, int& dirRow, int& dirCol)
{
	dirRow = 0;
	dirCol = 0;

	if (input == 'i' || input == 'I')
	{
		dirRow = -1;	// UP
	}
	else if (input == 'j' || input == 'J')
	{
		dirCol = -1;	// LEFT
	}
	else if (input == 'k' || input == 'K')
	{
		dirRow = 1;		// RIGHT
	}
	else if (input == 'l' || input == 'L')
	{
		dirCol = 1;		// DOWN
	}
	else return false;

	return true;
}

void Player::PlayerAttack(Entity* enemy)
{
	if (enemy != nullptr)
	{
		int dmg = getAttack();

		enemy->TakeDamage(dmg);

		cout << getName() << " attacks " << enemy->getName()
			<< " for " << dmg << " damage!" << endl;

		if (!enemy->IsAlive())
		{
			cout << enemy->getName() << " has been defeated!" << endl;
		}
		else
		{
			cout << enemy->getName() << " has "
				<< enemy->getHealth() << " HP left." << endl;
		}
	}
	else
	{
		cout << getName() << " attacks empty space. No enemy there." << endl;
	}
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
