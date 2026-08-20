#include "Player.h"
#include <iostream>
#include "Equipment.h"
#include "RNG.h"

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
	else if (input == 'q') {
		GetAttackRing();
		GetHpRing();
		GetSharkToothCharm();
		GetIdolTrinket();
		GetSilverBracelet();
		GetWoodCarvedNecklace();
		GetGemCharm();
		GetTreeEmblem();
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
void Player::GetAttackRing() {	//Indiv Accuracy addition
	AttackRing.AddAccuracy(5);
	AttackRing.AddDamage(4);
}
void Player::GetHpRing() {
	HpRing.AddAccuracy(5);
	HpRing.AddHealth(10);

	setHealth(getHealth() + HpRing.GetHealth());
}
void Player::GetSharkToothCharm() {
	SharkToothCharm.AddAccuracy(5);
	SharkToothCharm.AddDamage(2);
}
void Player::GetIdolTrinket() {
	IdolTrinket.AddAccuracy(5);
	IdolTrinket.AddDamage(2);
	IdolTrinket.AddHealth(2);

	setHealth(getHealth() + HpRing.GetHealth());
}
void Player::GetSilverBracelet() {
	SilverBracelet.AddAccuracy(5);
	SilverBracelet.AddHealth(5);

	setHealth(getHealth() + HpRing.GetHealth());
}
void Player::GetWoodCarvedNecklace() {
	WoodCarvedNecklace.AddAccuracy(5);
	WoodCarvedNecklace.AddHealth(2);

	setHealth(getHealth() + HpRing.GetHealth());
}
void Player::GetGemCharm() {
	GemCharm.AddAccuracy(5);
	GemCharm.AddHealth(7);

	setHealth(getHealth() + HpRing.GetHealth());
}
void Player::GetTreeEmblem() {
	TreeEmblem.AddAccuracy(5);
	TreeEmblem.AddHealth(5);
	TreeEmblem.AddDamage(2);

	setHealth(getHealth() + HpRing.GetHealth());
}
int Player::GetAccuracy()
{
	return AttackRing.GetAccuracy()
		+ HpRing.GetAccuracy()
		+ SharkToothCharm.GetAccuracy()
		+ IdolTrinket.GetAccuracy()
		+ SilverBracelet.GetAccuracy()
		+ WoodCarvedNecklace.GetAccuracy()
		+ GemCharm.GetAccuracy()
		+ TreeEmblem.GetAccuracy();
}
int Player::GetEquipmentDamage()
{
	return AttackRing.GetDamage()
		+ HpRing.GetDamage()
		+ SharkToothCharm.GetDamage()
		+ IdolTrinket.GetDamage()
		+ SilverBracelet.GetDamage()
		+ WoodCarvedNecklace.GetDamage()
		+ GemCharm.GetDamage()
		+ TreeEmblem.GetDamage();
}
int Player::GetEquipmentHealth()
{
	return AttackRing.GetHealth()
		+ HpRing.GetHealth()
		+ SharkToothCharm.GetHealth()
		+ IdolTrinket.GetHealth()
		+ SilverBracelet.GetHealth()
		+ WoodCarvedNecklace.GetHealth()
		+ GemCharm.GetHealth()
		+ TreeEmblem.GetHealth();
}
void Player::PlayerAttack(Entity* enemy)
{
	if (enemy != nullptr)
	{
		RNG rng;
		rng.SetAccuracy(GetAccuracy()); //Equipment Accuracy
		rng.HitOrMiss();

		if (rng.GetDidHit()) {
			int dmg = getAttack() + GetEquipmentDamage();
			if (rng.CriticalHit(5))
			{
				dmg *= 2;
				cout << "CRITICAL HIT" << endl;
			}
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
int Player::GetTotalHealth()
{
	return getMaxHealth() + GetEquipmentHealth();
}
