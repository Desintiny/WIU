#include "Game.h"
#include <iostream>
#include <conio.h>
using namespace std;

Game::Game()
{
	gameRunning = true;
	char tempMapGrid[12][12] = {
		//    0    1    2    3    4    5    6    7    8    9    10	 11
			{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' },  // 0
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 1
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 2
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 3
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 4
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 5
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 6
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 7
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 8
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 9
			{ '+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+' },  // 10
			{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' }   // 11
	};

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			mapGrid[row][col] = tempMapGrid[row][col];
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
			displayGame();
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

	cout << "======= HAVENFALL =======" << endl;
	cout << "1. Start Game" << endl;
	cout << "2. Quit Game\n" << endl;
	cout << "Enter: ";
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

	cout << "Choose Your Path" << endl;
	cout << endl;
	cout << "[1] Berserker - Melee Class" << endl;
	cout << "[2] Archer - Ranged Class" << endl;
	cout << "[3] Mage - Magic Class" << endl;
	cout << "Choice: ";
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

void Game::displayGame()
{
	int healthPts = 40;
	int staminaPts = 10;
	string healthBar = "##########";
	string staminaBar = "##########";

	string enemyHealthBar = "##########";
	bool inCombat = true;

	cout << "\n\n";
	cout << "\033[33m";
	cout << "YOU (P)\t\t\t";

	if (inCombat)
	{
		cout << "\033[35m";
		cout << "ENEMY (E)" << endl;
	}

	// HEALTH in red
	cout << "\033[31m";
	cout << "HP [" << healthBar << "] ";

	cout << healthPts;
	cout << "/40\t";

	if (inCombat)
	{
		cout << "\033[31m";
		cout << "HP [" << enemyHealthBar << "] \n";
	}

	// STAMINA in blue
	cout << "\033[36m";
	cout << "ST [" << staminaBar << "] ";

	cout << staminaPts;
	cout <<  "/10\n" << endl;
	cout << "\033[0m";

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			cout << mapGrid[row][col] << ' ';
		}
		cout << endl;
	}

	cout << "[WASD] Move | [1] Attack | [2] Ability | [3] Guard" << endl;
}
