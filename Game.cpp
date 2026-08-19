#define STYLE_ORANGE "\033[33m"
#define STYLE_RED "\033[31m"
#define STYLE_PURPLE "\033[35m"
#define STYLE_BLUE "\033[36m"
#define STYLE_NONE "\033[0m"

#include "Game.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

Game::Game()
{
	gameRunning = true;
	player = nullptr;
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		enemy[i] = nullptr;
	}

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			bool isBorder = (row == 0 || row == 11 || col == 0 || col == 11);
			mapGrid[row][col] = isBorder ? '+' : '.';
		}
	}
}

Game::~Game()
{
	delete player;
	delete enemy;
}

void Game::Start()
{
	MainMenu();

	if (!gameRunning)
	{
		return;
	}

	//alonso code test//
	Story();

	char sym = ClassSelection();

	Item testPotion;
	testPotion.name = "Healing Salve";
	testPotion.healAmount = 10;
	inventory.addItem(testPotion);

	if (player == nullptr)
	{
		gameRunning = false;
		return;
	}

	PathChoice();

	// ------- SPAWN PLAYER AT THE LEFT SIDE OF THE MAP -------
	if (player != nullptr)
	{
		SpawnEntity(player, sym, 4, 1);
	}

	// ------- CREATE X NUMBER OF ENEMIES -------
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		enemy[i] = new Enemy("Enemy" + (i + 1));
	}

	// ------- SPAWN X NUMBER OF ENEMIES -------
	if (enemy != nullptr)
	{
		for (int i = 0; i < NUM_ENEMY; i++)
		{
			SpawnEntity(enemy[i], 'E', 2 + i, 8);
		}
	}

	system("cls");

	while (gameRunning)
	{
		DisplayGame(sym);

		char input = _getch();

		player->PlayerMovement(sym, input, mapGrid);
		player->PlayerAtkDirection(input, mapGrid);

		// Clears the the rest of the console text, so it doesn't show the previous map
		system("cls");
	}
}

// ------------- SPAWN ENTITIES ONTO THE MAP -------------

void Game::SpawnEntity(Entity* entity, char sym, int row, int col)
{
	entity->setRow(row);
	entity->setCol(col);
	mapGrid[row][col] = sym;
}

void Game::MainMenu()
{
	int option;

	cout << "============= HAVENFALL =============" << endl;
	cout << "\t   1. Start Game" << endl;
	cout << "\t   2. Quit Game" << endl;
	cout << "=====================================" << endl;

	cout << "\nEnter: ";
	cin >> option;

	if (option == 1)
	{
		gameRunning = true;
	}
	else if (option == 2)
	{
		gameRunning = false;
	}
}

char Game::ClassSelection()
{
	int choice;
	char sym = 'P';
	do
	{
		// ------------ DISPLAY OF PLAYER CLASSES ------------

		cout << "=====================================" << endl;
		cout << "Choose Your Path" << endl;
		cout << endl;
		cout << "[1] Berserker - Melee Class" << endl;
		cout << "[2] Archer - Ranged Class" << endl;
		cout << "[3] Mage - Magic Class" << endl;
		cout << "\nChoice: ";
		cin >> choice;

		delete player;
		player = nullptr;

		// ------------ PLAYER CLASSES ------------

		if (choice == 1)
		{
			player = new Berserker("Berserker");
			sym = 'B';
		}
		else if (choice == 2)
		{
			player = new Archer("Archer");
			sym = 'A';
		}
		else if (choice == 3)
		{
			player = new Mage("Mage");
			sym = 'M';
		}
		else
		{
			cout << "Invalid choice." << endl;
			gameRunning = false;
		}
	} while (choice < 1 || choice > 3);

	gameRunning = true;

	return sym;
}

// ------------ DISPLAY UI FOR THE USER ------------

void Game::DisplayGame(char sym)
{
	int displayHealth = player->getMaxHealth();
	int displayStamina = player->getMaxStamina();

	char healthBar[10];
	char staminaBar[10];
	char enemyHealthBar[10];

	for (int i = 0; i < 10; i++)
	{
		healthBar[i] = '#';
		staminaBar[i] = '#';
		enemyHealthBar[i] = '#';
	}

	bool inCombat = true;

	// ------------ PLAYER UI ------------

	cout << STYLE_ORANGE << "YOU (" << sym << ")\t\t\t";

	// ------------ ENEMY UI DURING COMBAT ------------

	if (inCombat)
	{
		cout << STYLE_PURPLE << "ENEMY (E)" << endl;
	}

	// ------------ PLAYER HEALTH ------------

	cout << STYLE_RED << "HP [";

	for (int i = 0; i < 10; i++)
	{
		cout << healthBar[i];
	}

	cout << "] " << player->getHealth() << '/' << displayHealth << "\t";;

	// ------------ ENEMY HEALTH DURING COMBAT ------------

	if (inCombat)
	{
		cout << "HP [";

		for (int i = 0; i < 10; i++)
		{
			cout << enemyHealthBar[i];
		}

		cout << "] \n";
	}

	// ------------ PLAYER STAMINA ------------

	cout << STYLE_BLUE << "ST [";

	for (int i = 0; i < 10; i++)
	{
		cout << staminaBar[i];
	}

	cout << "] " << player->getStamina() << '/' << displayStamina << "\n" << STYLE_NONE << endl;

	// ------------ GAME MAP ------------

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			cout << mapGrid[row][col] << ' ';
		}

		cout << endl;
	}

	cout << "\n[WASD] Move | [1] Attack | [2] Ability | [3] Guard" << endl;
	cout << "Position: Row " << player->getRow()
		 << ", Column " << player->getCol() << endl;
}

void Game::Story()
{
	cout << "\n=====================================" << endl;
	std::cout << "You lived in a small town, named Havenbrook, it was peaceful and buzzing with life." << std::endl;
	std::cout << "Until the peace was disturbed, bells rang, The Valdrek Empire invaded the town." << std::endl;
	std::cout << "The ruthless enemies had killed all you loved, but you managed to escape." << std::endl;
	std::cout << "Planting a deep seed of hatred, you vowed to take back what you own and avenge your loved ones." << std::endl;
}

//Alonso's code for path randomistion (Notes: The bools can be moved to the .h file if needed)
void Game::PathChoice()
{
	srand(time(0));

	int randeventnum1;
	int randeventnum2;
	int randeventnum3;

	bool eventdone1 = false;
	bool eventdone2 = false;
	bool eventdone3 = false;
	bool eventdone4 = false;
	bool eventdone5 = false;
	bool eventdone6 = false;
	bool eventdone7 = false;
	bool eventdone8 = false;
	bool eventdone9 = false;
	bool eventdone10 = false;
	bool eventdone11 = false;
	bool eventdone12 = false;
	bool eventdone13 = false;
	bool eventdone14 = false;
	bool eventdone15 = false;

	randeventnum1 = (rand() % 15) + 1;
	randeventnum2 = (rand() % 15) + 1;
	randeventnum3 = (rand() % 15) + 1;

	//random event 1 reroller (to ensure event 1 will always be a new event and that no older events repeat)
	while ((randeventnum1 == 1 && eventdone1 == true) ||
		(randeventnum1 == 2 && eventdone2 == true) ||
		(randeventnum1 == 3 && eventdone3 == true) ||
		(randeventnum1 == 4 && eventdone4 == true) ||
		(randeventnum1 == 5 && eventdone5 == true) ||
		(randeventnum1 == 6 && eventdone6 == true) ||
		(randeventnum1 == 7 && eventdone7 == true) ||
		(randeventnum1 == 8 && eventdone8 == true) ||
		(randeventnum1 == 9 && eventdone9 == true) ||
		(randeventnum1 == 10 && eventdone10 == true) ||
		(randeventnum1 == 11 && eventdone11 == true) ||
		(randeventnum1 == 12 && eventdone12 == true) ||
		(randeventnum1 == 13 && eventdone13 == true) ||
		(randeventnum1 == 14 && eventdone14 == true) ||
		(randeventnum1 == 15 && eventdone15 == true))
	{
		randeventnum1 = (rand() % 15) + 1;
	}

	//random event 2 reroller (to prevent duplication of same events)
	while ((randeventnum2 == 1 && eventdone1 == true) ||
		(randeventnum2 == 2 && eventdone2 == true) ||
		(randeventnum2 == 3 && eventdone3 == true) ||
		(randeventnum2 == 4 && eventdone4 == true) ||
		(randeventnum2 == 5 && eventdone5 == true) ||
		(randeventnum2 == 6 && eventdone6 == true) ||
		(randeventnum2 == 7 && eventdone7 == true) ||
		(randeventnum2 == 8 && eventdone8 == true) ||
		(randeventnum2 == 9 && eventdone9 == true) ||
		(randeventnum2 == 10 && eventdone10 == true) ||
		(randeventnum2 == 11 && eventdone11 == true) ||
		(randeventnum2 == 12 && eventdone12 == true) ||
		(randeventnum2 == 13 && eventdone13 == true) ||
		(randeventnum2 == 14 && eventdone14 == true) ||
		(randeventnum2 == 15 && eventdone15 == true) ||
		randeventnum2 == randeventnum1)
	{
		randeventnum2 = (rand() % 15) + 1;
	}

	//random event 3 reroller (to prevent duplication of events with 1 and 2)
	while ((randeventnum3 == 1 && eventdone1 == true) ||
		(randeventnum3 == 2 && eventdone2 == true) ||
		(randeventnum3 == 3 && eventdone3 == true) ||
		(randeventnum3 == 4 && eventdone4 == true) ||
		(randeventnum3 == 5 && eventdone5 == true) ||
		(randeventnum3 == 6 && eventdone6 == true) ||
		(randeventnum3 == 7 && eventdone7 == true) ||
		(randeventnum3 == 8 && eventdone8 == true) ||
		(randeventnum3 == 9 && eventdone9 == true) ||
		(randeventnum3 == 10 && eventdone10 == true) ||
		(randeventnum3 == 11 && eventdone11 == true) ||
		(randeventnum3 == 12 && eventdone12 == true) ||
		(randeventnum3 == 13 && eventdone13 == true) ||
		(randeventnum3 == 14 && eventdone14 == true) ||
		(randeventnum3 == 15 && eventdone15 == true) ||
		randeventnum3 == randeventnum2 ||
		randeventnum3 == randeventnum1)
	{
		randeventnum3 = (rand() % 15) + 1;
	}

	//Array of all the events
	std::string EventNames[16];
	EventNames[1] = "Campfire Rest";
	EventNames[2] = "Forest Cottage";
	EventNames[3] = "Flowing River";
	EventNames[4] = "Wandering Traveller";
	EventNames[5] = "Random Chest";
	EventNames[6] = "Waterfall";
	EventNames[7] = "Sudden Rain";
	EventNames[8] = "Medicinal Herbs";
	EventNames[9] = "Forgotten Training Grounds";
	EventNames[10] = "White Crow";
	EventNames[11] = "Apple Tree";
	EventNames[12] = "Bee Hive";
	EventNames[13] = "Fellow Adventurer";
	EventNames[14] = "Abandoned Caravan";
	EventNames[15] = "Giant Tree";

	cout << "=====================================" << endl;

	std::cout << "Pick a Path" << std::endl;

	std::cout << "Path 1: " << EventNames[randeventnum1] << std::endl;
	std::cout << "Path 2: " << EventNames[randeventnum2] << std::endl;
	std::cout << "Path 3: " << EventNames[randeventnum3] << std::endl;

	/*if ((randeventnum1 == 1 && eventdone1 != true ||
		randeventnum2 == 1 && eventdone1 != true ||
		randeventnum3 == 1 && eventdone1 != true))
	{
		std::cout << "Path 1: Campfire Rest" << std::endl;
	}
	if ((randeventnum1 == 2 && eventdone2 != true ||
		randeventnum2 == 2 && eventdone2 != true ||
		randeventnum3 == 2 && eventdone2 != true))
	{
		std::cout << "Path 1: Forest Cottage" << std::endl;
	}
	if ((randeventnum1 == 3 && eventdone3 != true ||
		randeventnum2 == 3 && eventdone3 != true ||
		randeventnum3 == 3 && eventdone3 != true))
	{
		std::cout << "Path 1: Flowing River" << std::endl;
	}
	if ((randeventnum1 == 4 && eventdone4 != true ||
		randeventnum2 == 4 && eventdone4 != true ||
		randeventnum3 == 4 && eventdone4 != true))
	{
		std::cout << "Path 1: Wandering Traveller" << std::endl;
	}
	if ((randeventnum1 == 5 && eventdone5 != true ||
		randeventnum2 == 5 && eventdone5 != true ||
		randeventnum3 == 5 && eventdone5 != true))
	{
		std::cout << "Path 1: Random Chest" << std::endl;
	}
	if ((randeventnum1 == 6 && eventdone6 != true ||
		randeventnum2 == 6 && eventdone6 != true ||
		randeventnum3 == 6 && eventdone6 != true))
	{
		std::cout << "Path 1: Waterfall" << std::endl;
	}*/
}