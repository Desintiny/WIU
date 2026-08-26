#include "Boss.h"
#include "RNG.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>

using namespace std;

Boss::Boss(string n) : Enemy(n)
{
	static const int HEALTH = 65;

	setHealth(HEALTH);
	setMaxHealth(HEALTH);
	setAttack(10);

	ImpSlash = 0;
	DarkExe = 0;
	EmpWrath = 0;

	setImperialSlash(12);
	setDarkExecution(20);
	setEmperorWrath(25);
}

Boss::~Boss()
{

}

void Boss::EnemyMovement(Entity* target, char mapGrid[12][12])
{
	// NONE
}

void Boss::StartBossFight(Player* player)
{
	bool battleRunning = true;

	while (battleRunning)
	{
		system("cls");

		DisplayBattle(player);

		cout << "\n=====================================\n";
		cout << "[1] Attack\n";
		cout << "[2] Abilities\n";
		cout << "[3] Inventory\n";
		cout << "=====================================\n";
		cout << "Choice: ";

		int choice;
		cin >> choice;

		bool playerTurnUsed = false;

		switch (choice)
		{
		case 1:
			player->PlayerAttack(this);

			cout << "\nYou attack " << getName() << "!\n";

			playerTurnUsed = true;
			break;

		case 2:
			// Ability menu goes here
			playerTurnUsed = true;
			break;

		case 3:
		{
			player->DisplayInventory();

			int itemChoice;

			cout << "\nChoose item: ";
			cin >> itemChoice;

			if (itemChoice > 0)
			{
				player->UseItem(itemChoice - 1);
				playerTurnUsed = true;
			}

			break;
		}

		default:
			cout << "\nInvalid choice!\n";
			cout << "Press any key...";
			_getch();
			continue;
		}

		if (!IsAlive())
		{
			system("cls");

			cout << getName() << " has been defeated!\n";

			GoodEndingDialog();

			battleRunning = false;

			break;
		}

		if (playerTurnUsed)
		{
			cout << "\n" << getName() << "'s turn!\n";

			BossTurn(player);

			if (!player->IsAlive())
			{
				cout << "\nYou have been defeated...\n";

				battleRunning = false;

				break;
			}
		}

		cout << "\nPress any key to continue...";
		_getch();
	}
}

void Boss::DisplayBattle(Player* player)
{
	cout << "=====================================\n";
	cout << "          BOSS BATTLE\n";
	cout << "=====================================\n\n";

	cout << "BOSS: " << getName() << endl;
	cout << "HP: " << getHealth() << "/" << getMaxHealth() << endl;

	cout << "\n-------------------------------------\n";

	cout << "PLAYER: " << player->getName() << endl;
	cout << "HP: " << player->getHealth() << "/" << player->getMaxHealth() << endl;
	cout << "ST: " << player->getStamina() << "/" << player->getMaxStamina() << endl;
	cout << "ATK: " << player->getAttack() << endl;

	cout << "-------------------------------------\n";
}

void Boss::EnemyAttack(Entity* target)
{
	if (target == nullptr)
	{
		return;
	}

	// Keep the merged disable-turn mechanic for the boss too.
	if (GetDisabledTurns() > 0)
	{
		cout << getName() << " is unable to attack!" << endl;
		SetDisabledTurns(GetDisabledTurns() - 1);
		return;
	}

	RNG rng;
	Player* player = dynamic_cast<Player*>(target);

	// Keep player dodge equipment/bonuses against boss attacks.
	if (player != nullptr)
	{
		rng.Dodge(player->getDodgeChance());
		if (rng.GetDodged())
		{
			return;
		}
	}

	int choice = 0;
	int dmg = 0;
	int percent = rand() % 100 + 1;

	static const int PERCENT_ATK = 40;
	static const int PERCENT_IMP = 65;
	static const int PERCENT_EXE = 80;
	static const int PERCENT_EMP = 90;

	if (percent <= PERCENT_ATK)
	{
		choice = 1;
		dmg = getAttack();
	}
	else if (percent <= PERCENT_IMP)
	{
		choice = 2;
		dmg = getImperialSlash();
	}
	else if (percent <= PERCENT_EXE)
	{
		choice = 3;
		dmg = getDarkExecution();
	}
	else if (percent <= PERCENT_EMP)
	{
		choice = 4;
		dmg = getEmperorWrath();
	}
	else
	{
		choice = 5;
		dmg = 0;
	}

	if (choice == 5)
	{
		cout << getName() << " missed!" << endl;
		return;
	}

	target->TakeDamage(dmg);

	if (choice == 1)
		cout << getName() << " attacks " << target->getName() << " for " << dmg << " damage!" << endl;
	else if (choice == 2)
		cout << getName() << " uses Imperial Slash for " << dmg << " damage!" << endl;
	else if (choice == 3)
		cout << getName() << " uses Dark Execution for " << dmg << " damage!" << endl;
	else if (choice == 4)
		cout << getName() << " uses Emperor's Wrath for " << dmg << " damage!" << endl;

	// Keep Thorns from the merged build.
	if (player != nullptr)
	{
		rng.Thorns(player->GetThornsChance());
		if (rng.GetThorns())
		{
			TakeDamage(dmg);
			cout << getName() << " takes " << dmg << " reflected damage!" << endl;
		}
	}

	if (!target->IsAlive())
	{
		cout << target->getName() << " has been defeated!" << endl;
	}
	else
	{
		cout << target->getName() << " has " << target->getHealth() << " HP left." << endl;
	}
}

void Boss::setImperialSlash(int a)
{
	ImpSlash = a;
}

int Boss::getImperialSlash()
{
	return ImpSlash;
}

void Boss::setDarkExecution(int a)
{
	DarkExe = a;
}

int Boss::getDarkExecution()
{
	return DarkExe;
}

void Boss::setEmperorWrath(int a)
{
	EmpWrath = a;
}

int Boss::getEmperorWrath()
{
	return EmpWrath;
}

void Boss::BossTurn(Player* player)
{
	cout << getName() << " attacks!\n";

	EnemyAttack(player);
}

void Boss::DisplayLine(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		clock_t start = clock();

		while (clock() - start < 20)
		{

		}

		cout << text[i];
		cout.flush();
	}

	cout << endl;

	_getch();
}

void Boss::ReadDialog(string section)
{
	ifstream file("BossDialogue.txt");

	string line;
	bool readingSection = false;

	while (getline(file, line))
	{
		if (line.length() > 0 && line[0] == '#')
		{
			continue;
		}

		if (line[0] == '[' && line[line.length() - 1] == ']')
		{
			string currentSection = line.substr(1, line.length() - 2);

			if (currentSection == section)
			{
				readingSection = true;
				continue;
			}
			else if (readingSection)
			{
				break;
			}
		}

		if (readingSection && !line.empty())
		{
			DisplayLine(line);
		}
	}

	file.close();
}

bool Boss::DisplayCutscene()
{
	int choice1 = 0;
	int choice2 = 0;

	ReadDialog("START");

	cout << endl;

	cout << "1. You don't know who I am?" << endl;
	cout << "2. The one who is going to end you." << endl;
	cout << "3. You had destroyed everything I ever had." << endl;
	cout << endl;

	cout << "Choice: ";
	cin >> choice1;

	cout << endl;

	if (choice1 == 1)
	{
		ReadDialog("CHOICE1_1");

		cout << endl;

		cout << "1. I will never join you." << endl;
		cout << "2. Why should I trust you?" << endl;
		cout << "3. I will join you." << endl;
		cout << endl;

		cout << "Choice: ";
		cin >> choice2;

		cout << endl;

		switch (choice2)
		{
		case 1:
			ReadDialog("CHOICE1_1_1");
			return InitiateFightDialog();

			break;
		case 2:
			ReadDialog("CHOICE1_1_2");
			return ValdrekOfferDialog();

			break;
		case 3:
			ReadDialog("CHOICE1_1_3");
			return BadEndingDialog();

			break;
		default:
			cout << "Invalid choice." << endl;
		}
	}
	else if (choice1 == 2)
	{
		ReadDialog("CHOICE1_2");

		cout << endl;

		cout << "1. I will destroy your empire." << endl;
		cout << "2. Enough talk. Fight me." << endl;
		cout << "3. I will join you." << endl;
		cout << endl;

		cout << "Choice: ";
		cin >> choice2;

		cout << endl;

		switch (choice2)
		{
		case 1:
			ReadDialog("CHOICE1_2_1");
			return InitiateFightDialog();

			break;
		case 2:
			ReadDialog("CHOICE1_2_2");
			return InitiateFightDialog();

			break;
		case 3:
			ReadDialog("CHOICE1_2_3");
			return BadEndingDialog();

			break;
		default:
			cout << "Invalid choice." << endl;
		}
	}
	else if (choice1 == 3)
	{
		ReadDialog("CHOICE1_3");

		cout << endl;

		cout << "1. I will never forgive you." << endl;
		cout << "2. I want to know what you are planning." << endl;
		cout << "3. I will join you." << endl;
		cout << endl;

		cout << "Choice: ";
		cin >> choice2;

		cout << endl;

		switch (choice2)
		{
		case 1:
			ReadDialog("CHOICE1_3_1");
			return InitiateFightDialog();

			break;
		case 2:
			ReadDialog("CHOICE1_3_2");
			return ValdrekOfferDialog();

			break;
		case 3:
			ReadDialog("CHOICE1_3_3");
			return BadEndingDialog();

			break;
		default:
			cout << "Invalid choice." << endl;
		}
	}
	else
	{
		cout << "Invalid choice." << endl;
	}

	return false;
}

bool Boss::ValdrekOfferDialog()
{
	cout << endl;

	int choice3;

	cout << "1. (Fight)" << endl;
	cout << "2. (Join Emperor Valdrek)" << endl;

	cout << "Choice: ";
	cin >> choice3;

	cout << endl;

	switch (choice3)
	{
	case 1: 
		ReadDialog("OFFER_1");
		return InitiateFightDialog();

		break;
	case 2:
		ReadDialog("OFFER_2");
		return BadEndingDialog();

		break;
	default:
		cout << "Invalid choice." << endl;
	}

	return false;
}

bool Boss::InitiateFightDialog()
{
	cout << endl;

	ReadDialog("FIGHT");

	cout << endl;

	cout << "========== BOSS BATTLE BEGINS ==========" << endl;
	cout << "========== EMPEROR VALDREK ==========" << endl;

	return false;
}

bool Boss::BadEndingDialog()
{
	cout << endl;

	ReadDialog("BAD_ENDING");

	cout << "=============================\n";
	cout << "          BAD ENDING         \n";
	cout << "=============================\n";

	return true;
}

void Boss::GoodEndingDialog()
{
	cout << endl;

	ReadDialog("GOOD_ENDING");

	cout << endl;

	cout << "=============================\n";
	cout << "           THE END           \n";
	cout << "=============================\n";
	cout << endl;
}