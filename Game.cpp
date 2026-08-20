#define STYLE_ORANGE "\033[33m"
#define STYLE_RED "\033[31m"
#define STYLE_PURPLE "\033[35m"
#define STYLE_BLUE "\033[36m"
#define STYLE_NONE "\033[0m"

#include "Game.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>

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

	StoryDialogue();

	char sym = ClassSelection();

	if (player == nullptr)
	{
		gameRunning = false;
		return;
	}

	event.PathChoice();

	cout << "\nPress any key to continue...";
	_getch();

	system("cls");

	// ------- SPAWN PLAYER AT THE LEFT SIDE OF THE MAP -------
	if (player != nullptr)
	{
		LoadScene(sym, 1);
	}

	while (gameRunning)
	{
		DisplayGame(sym);

		char input = _getch();

		if (input == 'i' || input == 'j' || input == 'k' || input == 'l' ||
			input == 'I' || input == 'J' || input == 'K' || input == 'L')
		{
			int dirRow, dirCol;
			if (player->PlayerAtkDirection(input, dirRow, dirCol))
			{
				bool hit = false;

				// Scan tiles from minRange to maxRange along the chosen direction.
				// A Berserker (1/1) only checks 1 tile away; an Archer (3/4) or Mage (2/3)
				// can hit further out, so class range actually matters now.
				for (int dist = player->getMinRange(); dist <= player->getMaxRange() && !hit; dist++)
				{
					int checkRow = player->getRow() + (dirRow * dist);
					int checkCol = player->getCol() + (dirCol * dist);

					for (int i = 0; i < NUM_ENEMY; i++)
					{
						if (enemy[i] != nullptr &&
							enemy[i]->getRow() == checkRow &&
							enemy[i]->getCol() == checkCol)
						{
							player->PlayerAttack(enemy[i]);

							if (!enemy[i]->IsAlive())
							{
								mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';

								delete enemy[i];
								enemy[i] = nullptr;

								bool allEnemiesDead = true;

								for (int j = 0; j < NUM_ENEMY; j++)
								{
									if (enemy[j] != nullptr)
									{
										allEnemiesDead = false;
										break;
									}
								}

								if (allEnemiesDead && scene.getCurrentScene() == 1)
								{
									mapGrid[4][11] = 'X';  // right border
									cout << "\nThe exit has opened.";
								}
								else if (allEnemiesDead && scene.getCurrentScene() == 2)
								{
									mapGrid[7][11] = 'X';
									cout << "\nThe exit has opened.";
								}
							}

							hit = true;
							break;
						}
					}
				}

				if (!hit)
				{
					cout << player->getName() << " attacks empty space. No enemy there." << endl;
				}
			}

			cout << "\nPress any key to continue...";
			_getch();
		}
		else
		{
			player->PlayerMovement(sym, input, mapGrid);

			// ---- ENEMY MOVEMENT (wanders after the player moves) ----
			for (int i = 0; i < NUM_ENEMY; i++)
			{
				if (enemy[i] != nullptr)
				{
					enemy[i]->EnemyMovement(mapGrid);
				}
			}
			CheckSceneExit(sym);
		}

		// ---- ENEMY ATTACK CHECK (runs every turn, regardless of what the player just did) ----
		// Any enemy standing next to the player (including diagonally) gets to attack.

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			if (enemy[i] != nullptr)
			{
				int rowDist = abs(enemy[i]->getRow() - player->getRow());
				int colDist = abs(enemy[i]->getCol() - player->getCol());

				// 4-directional adjacency only (matches player movement/attack) —
				// exactly one tile away on ONE axis, not both at once (no diagonals)
				if ((rowDist == 1 && colDist == 0) || (rowDist == 0 && colDist == 1))
				{
					enemy[i]->EnemyAttack(player);
				}
			}
		}

		if (!player->IsAlive())
		{
			cout << "\nYou have been defeated..." << endl;
			gameRunning = false;
		}

		// Clears the the rest of the console text, so it doesn't show the previous map
		system("cls");
	}
}

void Game::StoryDialogue()
{
	cout << "\n=====================================" << endl;
	cout << "You lived in a small town, named Havenbrook, it was peaceful and buzzing with life." << endl;
	cout << "Until the peace was disturbed, bells rang, The Valdrek Empire invaded the town." << endl;
	cout << "The ruthless enemies had killed all you loved, but you managed to escape." << endl;
	cout << "Planting a deep seed of hatred, you vowed to take back what you own and avenge your loved ones." << endl;
	cout << "=====================================\n" << endl;
	cout << "Press any key to continue...";
	_getch();
	system("cls");
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

	do
	{
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
		else
		{
			cout << "Invalid option. Try again.\n\n";
		}
	} while (option != 1);
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

	cout << "] " << player->getHealth() << '/' << displayHealth << "\t";

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

	if (scene.getCurrentScene() == 1)
	{
		cout << "FOREST\n";
	}
	else if (scene.getCurrentScene() == 2)
	{
		cout << "VILLAGE\n";
	}
	else
	{
		cout << "BOSS ARENA\n";
	}

	// ------------ GAME MAP ------------

	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			cout << mapGrid[row][col] << ' ';
		}

		cout << endl;
	}

	cout << "\n[WASD] Move | [IJKL] Attack" << endl;
	cout << "Position: Row " << player->getRow()
		<< ", Column " << player->getCol() << endl;
}

void Game::LoadScene(char sym, int sceneNumber)
{
	scene.ChangeScene(sceneNumber);

	ClearEnemies();

	// Rebuild the 12 x 12 map.
	for (int row = 0; row < 12; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			bool isBorder = (row == 0 || row == 11 || col == 0 || col == 11);
			mapGrid[row][col] = isBorder ? '+' : '.';
		}
	}
	// ------------------------- FOREST -------------------------
	if (sceneNumber == 1)
	{
		SpawnEntity(player, sym, 4, 1);

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			enemy[i] = new Enemy("Enemy" + std::to_string(i + 1));
		}

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			SpawnEntity(enemy[i], 'E', 2 + i, 8);
		}
	}
	// ------------------------- VILLAGE -------------------------
	else if (sceneNumber == 2)
	{
		SpawnEntity(player, sym, 4, 1);

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			enemy[i] = new Enemy("Village Enemy" + std::to_string(i + 1));
		}

		for (int i = 0; i < NUM_ENEMY; i++)
		{
			SpawnEntity(enemy[i], 'E', 2 + i, 8);
		}
	}
	// ------------------------- BOSS -------------------------
	else if (sceneNumber == 3)
	{
		SpawnEntity(player, sym, 7, 1);
	}
}

void Game::CheckSceneExit(char sym)
{
	int row = player->getRow();
	int col = player->getCol();

	if (scene.getCurrentScene() == 1 && row == 4 && col == 11) // X position
	{
		LoadScene(sym, 2);
	}
	else if (scene.getCurrentScene() == 2 && row == 7 && col == 11) // X position
	{
		LoadScene(sym, 3);
	}
}

void Game::ClearEnemies()
{
	for (int i = 0; i < NUM_ENEMY; i++)
	{
		delete enemy[i];
		enemy[i] = nullptr;
	}
}
