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

	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 12; col++) {
			bool isBorder = (row == 0 || row == 11 || col == 0 || col == 11);
			mapGrid[row][col] = isBorder ? '+' : '.';
		}
	}
}

Game::~Game() 
{

}

void Game::Start()
{
	int input;

	MainMenu();

	if (gameRunning)
	{
		ClassSelection();
		do 
		{
			DisplayGame();
			input = _getch();
		} while (gameRunning);
	}
	else
	{
		return;
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
	cout << "=====================================" << endl;
	cout << "Choose Your Path" << endl;
	cout << endl;
	cout << "[1] Berserker - Melee Class" << endl;
	cout << "[2] Archer - Ranged Class" << endl;
	cout << "[3] Mage - Magic Class" << endl;
	cout << "\nChoice: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << "player is now a berserker" << endl;
	}
	else if (choice == 2)
	{
		cout << "player is now an archer" << endl;
	}
	else if (choice == 3)
	{
		cout << "player is now a mage" << endl;
	}
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

	cout << "=====================================" << endl;

	// ------------ PLAYER DISPLAY ------------

	cout << STYLE_ORANGE << "YOU (P)\t\t\t";

	// ENEMY HEALTH (ONLY SHOWS WHEN IN COMBAT)

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

	cout << "] ";

	cout << healthPts;
	cout << "/40\t";

	// ENEMY HEALTH (ONLY SHOWS WHEN IN COMBAT)

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
	cout << "] ";

	cout << staminaPts;
	cout <<  "/10\n" << STYLE_NONE << endl;

	// ------------ GAME MAP ------------

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			cout << mapGrid[row][col] << ' ';
		}
		cout << endl;
	}

	// ------------ PLAYER CONTROLS ------------

	cout << "[WASD] Move | [1] Attack | [2] Ability | [3] Guard" << endl;
}
