#define STYLE_ORANGE "\033[33m"
#define STYLE_RED "\033[31m"
#define STYLE_PURPLE "\033[35m"
#define STYLE_BLUE "\033[36m"
#define STYLE_NONE "\033[0m"

#include "Game.h"
#include <iostream>
#include <conio.h>

using namespace std;

Game::Game()
{
	gameRunning = true;
	player = nullptr;

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
}

void Game::Start()
{
	MainMenu();

	if (!gameRunning)
	{
		return;
	}

	ClassSelection();

	if (player == nullptr)
	{
		gameRunning = false;
		return;
	}

	// Start the player at left side
	player->setRow(4);
	player->setCol(1);
	mapGrid[4][1] = 'P';

	system("cls");

	while (gameRunning)
	{
		DisplayGame();

		char input = _getch();

		player->PlayerMovement(input, mapGrid);

		// Clears the the rest of the console text, so it doesn't show the previous map
		system("cls");
	}
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

void Game::ClassSelection()
{
	int choice;
	do
	{
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

		if (choice == 1)
		{
			player = new Berserker("Berserker");
		}
		else if (choice == 2)
		{
			player = new Archer("Archer");
		}
		else if (choice == 3)
		{
			player = new Mage("Mage");
		}
		else
		{
			cout << "Invalid choice." << endl;
			gameRunning = false;
		}
	} while (choice < 1 || choice > 3);
}

void Game::DisplayGame()
{
	int healthPts = 40;
	int staminaPts = 10;

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

	cout << STYLE_ORANGE << "YOU (P)\t\t\t";

	if (inCombat)
	{
		cout << STYLE_PURPLE << "ENEMY (E)" << endl;
	}

	cout << STYLE_RED << "HP [";

	for (int i = 0; i < 10; i++)
	{
		cout << healthBar[i];
	}

	cout << "] " << healthPts << "/40\t";

	if (inCombat)
	{
		cout << "HP [";

		for (int i = 0; i < 10; i++)
		{
			cout << enemyHealthBar[i];
		}

		cout << "] \n";
	}

	cout << STYLE_BLUE << "ST [";

	for (int i = 0; i < 10; i++)
	{
		cout << staminaBar[i];
	}

	cout << "] " << staminaPts << "/10\n" << STYLE_NONE << endl;

	// ------------ GAME MAP ------------

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			cout << mapGrid[row][col] << ' ';
		}

		cout << endl;
	}

	cout << "\n[WASD] Move | [1] Attack | [2] Ability | [3] Guard | [Q] Quit" << endl;
	cout << "Position: Row " << player->getRow()
		 << ", Column " << player->getCol() << endl;
}
