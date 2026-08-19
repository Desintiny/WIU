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
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		delete enemy[i];
	}
}

void Game::Start()
{
	MainMenu();

	if (!gameRunning)
	{
		return;
	}

	char sym = ClassSelection();

	if (player == nullptr)
	{
		gameRunning = false;
		return;
	}

	// ------- SPAWN PLAYER AT THE LEFT SIDE OF THE MAP -------
	if (player != nullptr)
	{
		SpawnEntity(player, sym, 4, 1);
	}

	// ------- CREATE X NUMBER OF ENEMIES -------
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		enemy[i] = new Enemy("Enemy" + std::to_string(i + 1));
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

	int healthFilled = (player->getHealth() * 10) / player->getMaxHealth();
	int staminaFilled = (player->getStamina() * 10) / player->getMaxStamina();

	for (int i = 0; i < 10; i++)
	{
		healthBar[i] = (i < healthFilled) ? '#' : '-';
		staminaBar[i] = (i < staminaFilled) ? '#' : '-';
		enemyHealthBar[i] = '#'; // leave as-is until enemy HP tracking is wired into combat
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
