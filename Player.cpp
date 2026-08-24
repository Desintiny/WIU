#include "Player.h"
#include <iostream>

Player::Player(string n) : Entity(n)
{
	staminaPts = 0;
	maxStaminaPts = 0;

	minRange = 0;
	maxRange = 0;

	equippedWeaponBonus = 0;
	equippedWeaponName = "None";
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

// Same direction logic as PlayerAtkDirection, kept separate so ability targeting
// can diverge later (e.g. different key scheme or AoE) without touching basic attacks.
bool Player::PlayerAbilityDirection(char input, int& dirRow, int& dirCol)
{
	return PlayerAtkDirection(input, dirRow, dirCol);
}

void Player::GetAttackRing()
{
	AttackRing.AddAccuracy(2);
	AttackRing.AddDamage(4);
}

void Player::GetHpRing()
{
	HpRing.AddAccuracy(2);
	HpRing.AddHealth(10);

	setMaxHealth(getMaxHealth() + HpRing.GetHealth());
	setHealth(getHealth() + HpRing.GetHealth());
}

void Player::GetSharkToothCharm()
{
	SharkToothCharm.AddAccuracy(2);
	SharkToothCharm.AddDamage(2);
}

void Player::GetIdolTrinket()
{
	IdolTrinket.AddAccuracy(2);
	IdolTrinket.AddDamage(2);
	IdolTrinket.AddHealth(2);

	setMaxHealth(getMaxHealth() + IdolTrinket.GetHealth());
	setHealth(getHealth() + IdolTrinket.GetHealth());
}

void Player::GetSilverBracelet()
{
	SilverBracelet.AddAccuracy(2);
	SilverBracelet.AddHealth(5);

	setMaxHealth(getMaxHealth() + SilverBracelet.GetHealth());
	setHealth(getHealth() + SilverBracelet.GetHealth());
}

void Player::GetWoodCarvedNecklace()
{
	WoodCarvedNecklace.AddAccuracy(2);
	WoodCarvedNecklace.AddHealth(2);

	setMaxHealth(getMaxHealth() + WoodCarvedNecklace.GetHealth());
	setHealth(getHealth() + WoodCarvedNecklace.GetHealth());
}

void Player::GetGemCharm()
{
	GemCharm.AddAccuracy(2);
	GemCharm.AddHealth(7);

	setMaxHealth(getMaxHealth() + GemCharm.GetHealth());
	setHealth(getHealth() + GemCharm.GetHealth());
}

void Player::GetTreeEmblem()
{
	TreeEmblem.AddAccuracy(2);
	TreeEmblem.AddHealth(5);
	TreeEmblem.AddDamage(2);

	setMaxHealth(getMaxHealth() + TreeEmblem.GetHealth());
	setHealth(getHealth() + TreeEmblem.GetHealth());
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

void Player::AddItem(Item item)
{
    inventory.push_back(item);

    cout << "\nYou obtained: " << item.name << "!" << endl;
}


void Player::DisplayInventory()
{
    cout << "\n=====================================" << endl;
    cout << "              INVENTORY" << endl;
    cout << "=====================================" << endl;

    cout << "HP: " << getHealth()
        << "/" << getMaxHealth() << endl;

    cout << "ATK: " << getAttack() << endl;
    cout << "Weapon: " << equippedWeaponName << endl;

    cout << "-------------------------------------" << endl;

    if (inventory.empty())
    {
        cout << "Inventory is empty." << endl;
    }
    else
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << "[" << i + 1 << "] "
                << inventory[i].name << endl;

            cout << "    Type: "
                << inventory[i].type << endl;

            if (inventory[i].healAmount > 0)
            {
                cout << "    Heal: "
                    << inventory[i].healAmount
                    << " HP" << endl;
            }

            if (inventory[i].atkBonus > 0)
            {
                cout << "    ATK Bonus: +"
                    << inventory[i].atkBonus << endl;
            }

            cout << endl;
        }
    }

    cout << "-------------------------------------" << endl;
    cout << "[Item Number] Use Item" << endl;
    cout << "[0] Back" << endl;
    cout << "=====================================" << endl;
}


void Player::UseItem(int index)
{
    if (index < 0 || index >= inventory.size())
    {
        cout << "\nInvalid item." << endl;
        return;
    }

    Item item = inventory[index];

    // -------- HEALING ITEM --------
    if (item.type == "Healing")
    {
        int oldHealth = getHealth();

        int newHealth = getHealth() + item.healAmount;

        if (newHealth > getMaxHealth())
        {
            newHealth = getMaxHealth();
        }

        setHealth(newHealth);

        cout << "\nYou used "
            << item.name << "!" << endl;

        cout << "HP: "
            << oldHealth
            << " -> "
            << getHealth()
            << endl;
    }

    // -------- WEAPON --------
    else if (item.type == "Weapon")
    {
        int oldAttack = getAttack();

        // remove the previous weapon's bonus before applying the new one,
        // so switching weapons replaces rather than stacks
        setAttack(getAttack() - equippedWeaponBonus);

        equippedWeaponBonus = item.atkBonus;
        equippedWeaponName = item.name;

        setAttack(getAttack() + equippedWeaponBonus);

        cout << "\nYou equipped "
            << item.name << "!" << endl;

        cout << "ATK: "
            << oldAttack
            << " -> "
            << getAttack()
            << endl;
    }

    else
    {
        cout << "\nThis item cannot be used yet." << endl;
        return;
    }

    // Remove consumable items
    if (item.consumable)
    {
        inventory.erase(inventory.begin() + index);
    }
}

std::string Player::getEquippedWeaponName(void)
{
    return equippedWeaponName;
}
