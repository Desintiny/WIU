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
	enemyCount = 0;

	loopCount = 0;
	maxLoops = 6;

	exitUnlocked = false;
	encounterFinished = false;

	for (int i = 0; i < MAX_ENEMIES; i++)
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
	for (int i = 0; i < MAX_ENEMIES; i++)
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

	// ------- SPAWN PLAYER AT THE LEFT SIDE OF THE MAP -------
	if (player != nullptr)
	{
		event.PathChoice(player);

		cout << "\nPress any key to continue...";
		_getch();

		system("cls");

		LoadScene(sym, 1);
	}

	while (gameRunning)
	{
		DisplayGame(sym);

		char input = _getch();

		// -------- INVENTORY --------
		if (input == 'e' || input == 'E')
		{
			system("cls");

			player->DisplayInventory();

			int choice;

			cout << "\nChoice: ";
			cin >> choice;

			if (choice > 0)
			{
				player->UseItem(choice - 1);
			}

			cout << "\nPress any key to continue...";
			_getch();
		}

		// -------- ABILITIES --------
		else if (input == '2')
		{
			cout << "\n--- Abilities ---" << endl;
			cout << "[1] Fireball  [2] Magic Missile  [3] Blood Pierce" << endl;
			cout << "[4] Icicle Spear  [5] Lightning Bolt  [6] Blood Bomb" << endl;
			cout << "[7] Poison Shot  [8] Air Cutter  [9] Boulder Throw" << endl;
			cout << "[0] Water Bolt" << endl;

			char abilityChoice = _getch();

			if (abilityChoice >= '0' && abilityChoice <= '9')
			{
				cout << "\nInput a Direction [IJKL]: " << endl;

				char abilityDirection = _getch();

				if (abilityDirection == 'i' || abilityDirection == 'j' ||
					abilityDirection == 'k' || abilityDirection == 'l' ||
					abilityDirection == 'I' || abilityDirection == 'J' ||
					abilityDirection == 'K' || abilityDirection == 'L')
				{
					int abilityIndex = abilityChoice - '0';
					CastAbility(abilityIndex, abilityDirection);
				}
			}

			if (!encounterFinished)
			{
				cout << "\nPress any key to continue...";
				_getch();
			}
		}

		// -------- ATTACK --------
		else if (input == 'i' || input == 'j' ||
			input == 'k' || input == 'l' ||
			input == 'I' || input == 'J' ||
			input == 'K' || input == 'L')
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

					for (int i = 0; i < enemyCount; i++)
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

								for (int j = 0; j < enemyCount; j++)
								{
									if (enemy[j] != nullptr)
									{
										allEnemiesDead = false;
										break;
									}
								}

								if (allEnemiesDead && scene.getCurrentScene() == 1)
								{
									loopCount++;

									encounterFinished = true;

									cout << "\nEncounter completed!";
									cout << "\nProgress: "
										<< loopCount
										<< "/"
										<< maxLoops;
								}
								else if (allEnemiesDead && scene.getCurrentScene() == 2)
								{
									loopCount++;

									encounterFinished = true;

									cout << "\nEncounter completed!";
									cout << "\nProgress: "
										<< loopCount
										<< "/"
										<< maxLoops;
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

			if (!encounterFinished)
			{
				cout << "\nPress any key to continue...";
				_getch();
			}
		}
		else
		{
			player->PlayerMovement(sym, input, mapGrid);

			// ---- ENEMY MOVEMENT (wanders after the player moves) ----
			for (int i = 0; i < enemyCount; i++)
			{
				if (enemy[i] != nullptr)
				{
					enemy[i]->EnemyMovement(player, mapGrid);
				}
			}
		}

		// ---- ENEMY ATTACK CHECK (runs every turn, regardless of what the player just did) ----
		// Any enemy standing next to the player (including diagonally) gets to attack.
		
		for (int i = 0; i < enemyCount; i++)
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

		if (encounterFinished)
		{
			encounterFinished = false;

			cout << "\nPress any key to continue...";
			_getch();

			system("cls");


			// =====================================
			// MORE ENCOUNTERS REMAIN
			// =====================================

			if (loopCount < 3)
			{
				// Pick another event
				event.PathChoice(player);

				cout << "\nPress any key to continue...";
				_getch();

				system("cls");

				// Start another combat encounter
				LoadScene(sym, 1);
			}
			else if (loopCount < 6)
			{
				// Pick another event
				event.PathChoice(player);

				cout << "\nPress any key to continue...";
				_getch();

				system("cls");

				// Start another combat encounter
				LoadScene(sym, 2);
			}

			// =====================================
			// ALL ENCOUNTERS COMPLETE
			// =====================================

			else if (loopCount == maxLoops)
			{
				cout << "=====================================\n";
				cout << "          STAGE COMPLETE\n";
				cout << "=====================================\n";
				cout << "The boss awaits...\n";

				cout << "\nPress any key to continue...";
				_getch();

				system("cls");

				// Load Boss Arena
				LoadScene(sym, 3);
			}
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

	int healthFilled = (player->getHealth() * 10) / player->getMaxHealth();
	int staminaFilled = (player->getStamina() * 10) / player->getMaxStamina();

	for (int i = 0; i < 10; i++)
	{
		healthBar[i] = (i < healthFilled) ? '#' : '-';
		staminaBar[i] = (i < staminaFilled) ? '#' : '-';
	}

	// ------------ PLAYER UI ------------

	cout << STYLE_ORANGE << "YOU (" << sym << ")\t\t\t";
	cout << endl;

	// ------------ PLAYER HEALTH ------------

	cout << STYLE_RED << "HP [";

	for (int i = 0; i < 10; i++)
	{
		cout << healthBar[i];
	}

	cout << "] " << player->getHealth() << '/' << displayHealth << "\t";
	cout << endl;

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

	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			DisplayEnemyHP(enemy[i]);
		}
	}

	cout << "\n[WASD] Move | [IJKL] Attack | [2] Abilities | [E] Inventory" << endl;
	cout << "Position: Row " << player->getRow()
		 << ", Column " << player->getCol() << endl;
}

void Game::DisplayEnemyHP(Entity* enemy)
{
	if (enemy == nullptr)
	{
		return;
	}

	char enemyHealthBar[10];

	int healthFilled = (enemy->getHealth() * 10) / enemy->getMaxHealth();

	for (int i = 0; i < 10; i++)
	{
		enemyHealthBar[i] = (i < healthFilled) ? '#' : '-';
	}

	cout << STYLE_PURPLE
		<< enemy->getName()
		<< STYLE_RED
		<< " HP [";

	for (int i = 0; i < 10; i++)
	{
		cout << enemyHealthBar[i];
	}

	cout << "] "
		<< enemy->getHealth()
		<< '/' << enemy->getMaxHealth()
		<< STYLE_NONE << endl;
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

		enemyCount = ENEMY_FOREST;

		enemy[0] = new Slime("Slime");
		SpawnEntity(enemy[0], 'S', 2, 8);

		enemy[1] = new Goblin("Goblin");
		SpawnEntity(enemy[1], 'G', 6, 8);

		enemy[2] = new WildBoar("Wild Boar");
		SpawnEntity(enemy[2], 'W', 10, 8);
	}
	// ------------------------- VILLAGE -------------------------
	else if (sceneNumber == 2)
	{
		SpawnEntity(player, sym, 4, 1);

		enemyCount = ENEMY_VILLAGE;

		enemy[0] = new ValSwordman("Valdrek Swordman");
		SpawnEntity(enemy[0], 'S', 2, 8);

		enemy[1] = new ValEnforcer("Valdrek Enforcer");
		SpawnEntity(enemy[1], 'E', 4, 8);

		enemy[2] = new ValArcher("Valdrek Archer");
		SpawnEntity(enemy[2], 'A', 6, 8);
	}
	// ------------------------- BOSS -------------------------
	else if (sceneNumber == 3)
	{
		SpawnEntity(player, sym, 7, 1);

		enemyCount = ENEMY_BOSS;

		enemy[0] = new ValSwordman("Valdrek");
		SpawnEntity(enemy[0], 'V', 7, 8);
	}
}

void Game::ClearEnemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		delete enemy[i];
		enemy[i] = nullptr;
	}

	enemyCount = 0;
}

void Game::CastAbility(int abilityChoice, char direction)
{
	int dirRow, dirCol;

	if (!player->PlayerAbilityDirection(direction, dirRow, dirCol))
	{
		return;
	}

	const int abilityRangeMin = 1;
	const int abilityRangeMax = 3;

	bool hit = false;

	for (int dist = abilityRangeMin; dist <= abilityRangeMax && !hit; dist++)
	{
		int checkRow = player->getRow() + (dirRow * dist);
		int checkCol = player->getCol() + (dirCol * dist);

		for (int i = 0; i < enemyCount; i++)
		{
			if (enemy[i] != nullptr &&
				enemy[i]->getRow() == checkRow &&
				enemy[i]->getCol() == checkCol)
			{
				switch (abilityChoice)
				{
					case 1: Ability.Fireball(*enemy[i]); cout << player->getName() << " casts Fireball on " << enemy[i]->getName() << "!" << endl; break;
					case 2: Ability.MagicMissile(*enemy[i]); cout << player->getName() << " casts Magic Missile on " << enemy[i]->getName() << "!" << endl; break;
					case 3: Ability.BloodPierce(*enemy[i], *player); cout << player->getName() << " casts Blood Pierce on " << enemy[i]->getName() << "!" << endl; break;
					case 4: Ability.IcicleSpear(*enemy[i]); cout << player->getName() << " casts Icicle Spear on " << enemy[i]->getName() << "!" << endl; break;
					case 5: Ability.LightningBolt(*enemy[i]); cout << player->getName() << " casts Lightning Bolt on " << enemy[i]->getName() << "!" << endl; break;
					case 6: Ability.BloodBomb(*enemy[i], *player); cout << player->getName() << " casts Blood Bomb on " << enemy[i]->getName() << "!" << endl; break;
					case 7: Ability.PoisonShot(*enemy[i]); cout << player->getName() << " casts Poison Shot on " << enemy[i]->getName() << "!" << endl; break;
					case 8: Ability.Aircutter(*enemy[i]); cout << player->getName() << " casts Air Cutter on " << enemy[i]->getName() << "!" << endl; break;
					case 9: Ability.BoulderThrow(*enemy[i]); cout << player->getName() << " casts Boulder Throw on " << enemy[i]->getName() << "!" << endl; break;
					case 0: Ability.WaterBolt(*enemy[i]); cout << player->getName() << " casts Water Bolt on " << enemy[i]->getName() << "!" << endl; break;
					default: cout << "Invalid ability." << endl; break;
				}

				if (enemy[i]->IsAlive())
				{
					cout << enemy[i]->getName() << " has " << enemy[i]->getHealth() << " HP left." << endl;
				}
				else
				{
					cout << enemy[i]->getName() << " has been defeated!" << endl;

					mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';

					delete enemy[i];
					enemy[i] = nullptr;

					bool allEnemiesDead = true;

					for (int j = 0; j < enemyCount; j++)
					{
						if (enemy[j] != nullptr)
						{
							allEnemiesDead = false;
							break;
						}
					}

					if (allEnemiesDead && (scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2))
					{
						loopCount++;
						encounterFinished = true;

						cout << "\nEncounter completed!";
						cout << "\nProgress: " << loopCount << "/" << maxLoops;
					}
				}

				// If this player also took self-damage (Blood Pierce / Blood Bomb),
				// the caster HP is already reduced by TakeDamage inside the ability call.
				if (!player->IsAlive())
				{
					cout << "\nYou have been defeated..." << endl;
					gameRunning = false;
				}

				hit = true;
				break;
			}
		}
	}

	if (!hit)
	{
		cout << player->getName() << " casts the ability at empty space. No enemy there." << endl;
	}
}
