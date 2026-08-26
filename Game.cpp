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

	//TESTING CODE FOR ABILITY PICKER RANDOMISER
	//USED TO PICK 3 RANDOMISED ABILITIES AT THE START (NO DESCRIPTION GIVEN TO PLAYERS, LET THEM FIND OUT THEMSELVES)
	randomAbilityPicker();

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
		// Apply existing damage-over-time effects at the START of the next turn.
		// This means Fireball / Icicle Spear / Poison Shot do not tick immediately
		// on the same turn they are cast.
		TickEnemyDoT();

		// A DoT tick may kill the last enemy and finish the encounter.
		if (encounterFinished)
		{
			// Skip player input this turn so the normal encounter-finished
			// section below can move to the next event/scene.
		}
		else
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
			// NEW CODE HERE //
			// TESTING ABILITY RANDOMISATION //
			else if (input == '2')
			{
				cout << "\n--- Abilities ---" << endl;

				if (Ability.RandoAbilityBools[1] == true)
				{
					cout << "[1] Fireball (rng "
						<< Ability.GetMinRange(Abilities::FIREBALL) << "-"
						<< Ability.GetMaxRange(Abilities::FIREBALL) << ")  ";
				}

				if (Ability.RandoAbilityBools[2] == true)
				{
					cout << "[2] Boulder Throw (rng "
						<< Ability.GetMinRange(Abilities::BOULDER_THROW) << "-"
						<< Ability.GetMaxRange(Abilities::BOULDER_THROW) << ")  ";
				}

				if (Ability.RandoAbilityBools[3] == true)
				{
					cout << "[3] Blood Pierce (rng "
						<< Ability.GetMinRange(Abilities::BLOOD_PIERCE) << "-"
						<< Ability.GetMaxRange(Abilities::BLOOD_PIERCE) << ")  ";
				}

				if (Ability.RandoAbilityBools[4] == true)
				{
					cout << "[4] Poison Shot (rng "
						<< Ability.GetMinRange(Abilities::POISON_SHOT) << "-"
						<< Ability.GetMaxRange(Abilities::POISON_SHOT) << ")  ";
				}

				if (Ability.RandoAbilityBools[5] == true)
				{
					cout << "[5] Lightning Bolt (rng "
						<< Ability.GetMinRange(Abilities::LIGHTNING_BOLT) << "-"
						<< Ability.GetMaxRange(Abilities::LIGHTNING_BOLT) << ")  ";
				}

				if (Ability.RandoAbilityBools[6] == true)
				{
					cout << "[6] Blood Bomb (rng "
						<< Ability.GetMinRange(Abilities::BLOOD_BOMB) << "-"
						<< Ability.GetMaxRange(Abilities::BLOOD_BOMB) << ")  ";
				}

				if (Ability.RandoAbilityBools[7] == true)
				{
					cout << "[7] Water Bolt (rng "
						<< Ability.GetMinRange(Abilities::WATER_BOLT) << "-"
						<< Ability.GetMaxRange(Abilities::WATER_BOLT) << ")  ";
				}

				if (Ability.RandoAbilityBools[8] == true)
				{
					cout << "[8] Air Cutter (rng "
						<< Ability.GetMinRange(Abilities::AIR_CUTTER) << "-"
						<< Ability.GetMaxRange(Abilities::AIR_CUTTER) << ")  ";
				}

				if (Ability.RandoAbilityBools[9] == true)
				{
					cout << "[9] Blooming Flowers (rng "
						<< Ability.GetMinRange(Abilities::BLOOMING_FLOWER) << "-"
						<< Ability.GetMaxRange(Abilities::BLOOMING_FLOWER) << ")  ";
				}

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


			//TESTING CLASS ABILITY CODE
			//DONT TOUCH FOR NOW
			else if (input == 'Q' || input == 'q')
			{
				cout << "\n--- Class Abilities ---" << endl;

				
				{
					cout << "[1] Hero's Light (rng "
						<< Ability.GetMinClsAbiRange(Abilities::HEROS_LIGHT) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::HEROS_LIGHT) << ")  ";
				}

				
				{
					cout << "[2] Sworvant (rng "
						<< Ability.GetMinClsAbiRange(Abilities::SWORVANT) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::SWORVANT) << ")  ";
				}


				{
					cout << "[3] Sworvant:Sacrifice (rng "
						<< Ability.GetMinClsAbiRange(Abilities::SWORVANT_SACRIFICE) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::SWORVANT_SACRIFICE) << ")  ";
				}
				
				cout << "\n";
				
				{
					cout << "[4] Magic Missile (rng "
						<< Ability.GetMinClsAbiRange(Abilities::MAGIC_MISSILE) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::MAGIC_MISSILE) << ")  ";
				}

				
				{
					cout << "[5] Catclysm (rng "
						<< Ability.GetMinClsAbiRange(Abilities::CATCLYSM) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::CATCLYSM) << ")  ";
				}

				
				{
					cout << "[6] Icicle Spear (rng "
						<< Ability.GetMinClsAbiRange(Abilities::ICICLE_SPEAR) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::ICICLE_SPEAR) << ")  ";
				}

				cout << "\n";
				
				{
					cout << "[7] Magic Arrow (rng "
						<< Ability.GetMinClsAbiRange(Abilities::MAGIC_ARROW) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::MAGIC_ARROW) << ")  ";
				}

				
				{
					cout << "[8] Bullseye (rng "
						<< Ability.GetMinClsAbiRange(Abilities::BULLSEYE) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::BULLSEYE) << ")  ";
				}

				
				{
					cout << "[9] Phoenix Arrow (rng "
						<< Ability.GetMinClsAbiRange(Abilities::PHOENIX_ARROW) << "-"
						<< Ability.GetMaxClsAbiRange(Abilities::PHOENIX_ARROW) << ")  ";
				}

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
						CastClassAbility(abilityIndex, abilityDirection);
					}
				}

				if (!encounterFinished)
				{
					cout << "\nPress any key to continue...";
					_getch();
				}
			}

			//TEST CODE ENDS HERE

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
			}

			// ============================================================
			// ENEMY TURN
			// ============================================================
			// Each enemy gets ONE action per turn:
			// - If already beside the player, attack.
			// - Otherwise, move only.
			//
			// This prevents an enemy from moving next to the player and
			// attacking during the same turn.
			if (!encounterFinished)
			{
				for (int i = 0; i < enemyCount; i++)
				{
					if (enemy[i] != nullptr)
					{
						int rowDist = abs(enemy[i]->getRow() - player->getRow());
						int colDist = abs(enemy[i]->getCol() - player->getCol());

						bool besidePlayer =
							(rowDist == 1 && colDist == 0) ||
							(rowDist == 0 && colDist == 1);

						if (besidePlayer)
						{
							// Enemy was already beside the player before
							// taking its action, so it attacks.
							enemy[i]->EnemyAttack(player);
						}
						else
						{
							// Enemy is not beside the player, so its whole
							// action this turn is movement.
							enemy[i]->EnemyMovement(player, mapGrid);
						}

						if (!player->IsAlive())
						{
							break;
						}
					}
				}
			}

			if (!player->IsAlive())
			{
				cout << "\nYou have been defeated..." << endl;
				gameRunning = false;
			}
		} // end normal player/enemy turn

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

void Game::DisplayEnemyHP(Enemy* enemy)
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

int Game::RandNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
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

		enemyCount = RandNumber(2, 5); // 2-5 forest enemies

		for (int i = 0; i < enemyCount; i++)
		{
			int enemyType = RandNumber(1, 3);

			if (enemyType == 1)
			{
				enemy[i] = new Slime("Slime");
			}
			else if (enemyType == 2)
			{
				enemy[i] = new Goblin("Goblin");
			}
			else
			{
				enemy[i] = new WildBoar("Wild Boar");
			}

			int row;
			int col;

			// Check if that tile is an empty space
			do
			{
				// Spawn enemies on the left

				row = RandNumber(1, 10);
				col = RandNumber(5, 10);
			} while (mapGrid[row][col] != '.');

			char symbol;

			if (enemyType == 1)
			{
				symbol = 'S';
			}
			else if (enemyType == 2)
			{
				symbol = 'G';
			}
			else
			{
				symbol = 'W';
			}

			SpawnEntity(enemy[i], symbol, row, col);
		}
	}
	// ------------------------- VILLAGE -------------------------
	else if (sceneNumber == 2)
	{
		SpawnEntity(player, sym, 4, 1);

		enemyCount = RandNumber(2, 5); // 2-5 village enemies

		for (int i = 0; i < enemyCount; i++)
		{
			int enemyType = RandNumber(1, 3);

			if (enemyType == 1)
			{
				enemy[i] = new ValSwordman("Valdrek Swordman");
			}
			else if (enemyType == 2)
			{
				enemy[i] = new ValEnforcer("Valdrek Enforcer");
			}
			else
			{
				enemy[i] = new ValArcher("Valdrek Archer");
			}

			int row;
			int col;

			// Check if that tile is an empty space
			do
			{
				// Spawn enemies on the left

				row = RandNumber(1, 10);
				col = RandNumber(5, 10);
			} while (mapGrid[row][col] != '.');

			char symbol;

			if (enemyType == 1)
			{
				symbol = 'S';
			}
			else if (enemyType == 2)
			{
				symbol = 'E';
			}
			else
			{
				symbol = 'A';
			}

			SpawnEntity(enemy[i], symbol, row, col);
		}
	}
	// ------------------------- BOSS -------------------------
	else if (sceneNumber == 3)
	{
		SpawnEntity(player, sym, 7, 1);

		enemyCount = ENEMY_BOSS;

		enemy[0] = new ValEnforcer("Valdrek");
		SpawnEntity(enemy[0], 'E', 7, 8);
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

void Game::TickEnemyDoT()
{
	bool anyDotDamage = false;

	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i] == nullptr)
		{
			continue;
		}

		int healthBefore = enemy[i]->getHealth();

		// TickDoT() only deals damage when this enemy currently has a DoT.
		enemy[i]->TickDoT();

		if (enemy[i]->getHealth() < healthBefore)
		{
			anyDotDamage = true;

			cout << enemy[i]->getName()
				<< " takes "
				<< (healthBefore - enemy[i]->getHealth())
				<< " damage from a damage-over-time effect!" << endl;

			if (enemy[i]->IsAlive())
			{
				cout << enemy[i]->getName()
					<< " has "
					<< enemy[i]->getHealth()
					<< " HP left." << endl;
			}
			else
			{
				cout << enemy[i]->getName()
					<< " has been defeated by the damage-over-time effect!"
					<< endl;

				mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';

				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	// If DoT killed an enemy, check whether that was the final enemy.
	if (anyDotDamage)
	{
		bool allEnemiesDead = true;

		for (int i = 0; i < enemyCount; i++)
		{
			if (enemy[i] != nullptr)
			{
				allEnemiesDead = false;
				break;
			}
		}

		if (allEnemiesDead &&
			(scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2))
		{
			loopCount++;
			encounterFinished = true;

			cout << "\nEncounter completed!";
			cout << "\nProgress: " << loopCount << "/" << maxLoops;
		}
	}

	if (anyDotDamage && !encounterFinished)
	{
		cout << "\nPress any key to continue...";
		_getch();
		system("cls");
	}
}


void Game::CastAbility(int abilityChoice, char direction)
{
	int dirRow, dirCol;

	if (!player->PlayerAbilityDirection(direction, dirRow, dirCol))
	{
		return;
	}

	// Blood Pierce can hit up to 2 enemies in a straight line.
	// The player pays the 5 HP cost once, only if at least one enemy is hit.
	if (abilityChoice == 3)
	{
		int enemyHits = 0;
		const int maxTargets = 2;
		int pierceRangeMin = Ability.GetMinRange(Abilities::BLOOD_PIERCE);
		int pierceRangeMax = Ability.GetMaxRange(Abilities::BLOOD_PIERCE);

		for (int dist = pierceRangeMin; dist <= pierceRangeMax && enemyHits < maxTargets; dist++)
		{
			int checkRow = player->getRow() + (dirRow * dist);
			int checkCol = player->getCol() + (dirCol * dist);

			for (int i = 0; i < enemyCount; i++)
			{
				if (enemy[i] != nullptr &&
					enemy[i]->getRow() == checkRow &&
					enemy[i]->getCol() == checkCol)
				{
					Ability.BloodPierce(*enemy[i]);
					cout << player->getName() << " casts Blood Pierce on "
						<< enemy[i]->getName() << "!" << endl;

					if (enemy[i]->IsAlive())
					{
						cout << enemy[i]->getName() << " has "
							<< enemy[i]->getHealth() << " HP left." << endl;
					}
					else
					{
						cout << enemy[i]->getName() << " has been defeated!" << endl;
						mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';
						delete enemy[i];
						enemy[i] = nullptr;
					}

					enemyHits++;
					break;
				}
			}
		}

		if (enemyHits == 0)
		{
			cout << player->getName()
				<< " casts Blood Pierce at empty space. No enemy there." << endl;
		}
		else
		{
			player->TakeDamage(5);

			bool allEnemiesDead = true;
			for (int j = 0; j < enemyCount; j++)
			{
				if (enemy[j] != nullptr)
				{
					allEnemiesDead = false;
					break;
				}
			}

			if (allEnemiesDead &&
				(scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2))
			{
				loopCount++;
				encounterFinished = true;
				cout << "\nEncounter completed!";
				cout << "\nProgress: " << loopCount << "/" << maxLoops;
			}

			if (!player->IsAlive())
			{
				cout << "\nYou have been defeated..." << endl;
				gameRunning = false;
			}
		}

		return;
	}

	int abilityId;

	switch (abilityChoice)
	{
	case 1: abilityId = Abilities::FIREBALL; break;
	case 2: abilityId = Abilities::BOULDER_THROW; break;
	case 3: abilityId = Abilities::BLOOD_PIERCE; break;
	case 4: abilityId = Abilities::POISON_SHOT; break;
	case 5: abilityId = Abilities::LIGHTNING_BOLT; break;
	case 6: abilityId = Abilities::BLOOD_BOMB; break;
	case 7: abilityId = Abilities::WATER_BOLT; break;
	case 8: abilityId = Abilities::AIR_CUTTER; break;
	case 9: abilityId = Abilities::BLOOMING_FLOWER; break;
	default:
		cout << "Invalid ability." << endl;
		return;
	}

	int abilityRangeMin = Ability.GetMinRange(abilityId);
	int abilityRangeMax = Ability.GetMaxRange(abilityId);

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
				case 1: if (Ability.RandoAbilityBools[1] == true)
				{
					Ability.Fireball(*enemy[i]); cout << player->getName() << " casts Fireball on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 2: if (Ability.RandoAbilityBools[2] == true)
				{
					Ability.BoulderThrow(*enemy[i]); cout << player->getName() << " casts Boulder Throw on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 3: if (Ability.RandoAbilityBools[3] == true)
				{
					Ability.BloodPierce(*enemy[i]); cout << player->getName() << " casts Blood Pierce on " << enemy[i]->getName() << " and " << player->getName() << " sacrifices 5 HP!" << endl; break;
				}
				case 4: if (Ability.RandoAbilityBools[4] == true)
				{
					Ability.PoisonShot(*enemy[i]); cout << player->getName() << " casts Poison Shot on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 5: if (Ability.RandoAbilityBools[5] == true)
				{
					Ability.LightningBolt(*enemy[i]); cout << player->getName() << " casts Lightning Bolt on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 6: if (Ability.RandoAbilityBools[6] == true)
				{
					Ability.BloodBomb(*enemy[i], *player); cout << player->getName() << " casts Blood Bomb on " << enemy[i]->getName() << " and " << player->getName() << " sacrifices 10 HP!" << endl; break;
				}
				case 7: if (Ability.RandoAbilityBools[7] == true)
				{
					Ability.WaterBolt(*enemy[i], *player); cout << player->getName() << " casts Water Bolt on " << enemy[i]->getName() << " and " << player->getName() << " heals 5 HP!" << endl; break; 
					//added new words to make it make more sense
				}
				case 8: if (Ability.RandoAbilityBools[8] == true)
				{
					Ability.Aircutter(*enemy[i]); cout << player->getName() << " casts Air Cutter on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 9: if (Ability.RandoAbilityBools[9] == true)
				{
					Ability.BloomingFlowers(*enemy[i], *player); cout << player->getName() << " casts Blooming Flowers on " << enemy[i]->getName() << " and " << player->getName() << " heals 4 HP!" << endl; break;
				}
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

// NEW CODE HERE //
// TESTING ABILITY RANDOMISATION //
void Game::randomAbilityPicker()
{
	Ability.abilityans1;
	Ability.abilityans2;

	Ability.randoability1 = (rand() % 9) + 1;
	Ability.randoability2 = (rand() % 9) + 1;
	Ability.randoability3 = (rand() % 9) + 1;
	Ability.randoability4 = (rand() % 9) + 1;
	Ability.randoability5 = (rand() % 9) + 1;
	Ability.randoability6 = (rand() % 9) + 1;


	//random ability number generators
	while (Ability.randoability2 == Ability.randoability1)
	{
		Ability.randoability2 = (rand() % 9) + 1;
	}
	while (Ability.randoability3 == Ability.randoability1 || Ability.randoability3 == Ability.randoability2)
	{
		Ability.randoability3 = (rand() % 9) + 1;
	}
	while (Ability.randoability4 == Ability.randoability1 || Ability.randoability4 == Ability.randoability2 || Ability.randoability4 == Ability.randoability3)
	{
		Ability.randoability4 = (rand() % 9) + 1;
	}
	while (Ability.randoability5 == Ability.randoability1 || Ability.randoability5 == Ability.randoability2 || Ability.randoability5 == Ability.randoability3 ||
		Ability.randoability5 == Ability.randoability4)
	{
		Ability.randoability5 = (rand() % 9) + 1;
	}
	while (Ability.randoability6 == Ability.randoability1 || Ability.randoability6 == Ability.randoability2 || Ability.randoability6 == Ability.randoability3 ||
		Ability.randoability6 == Ability.randoability4 || Ability.randoability6 == Ability.randoability5)
	{
		Ability.randoability6 = (rand() % 9) + 1;
	}

	std::cout << "Pick 2 out of these 6 abilities" << std::endl;
	std::cout << "This will be your starter ability" << std::endl;
	std::cout << "\nAbility Choice 1: " << Ability.RandoAbilityList[Ability.randoability1] << std::endl;
	std::cout << "Ability Choice 2: " << Ability.RandoAbilityList[Ability.randoability2] << std::endl;
	std::cout << "Ability Choice 3: " << Ability.RandoAbilityList[Ability.randoability3] << std::endl;
	std::cout << "Ability Choice 4: " << Ability.RandoAbilityList[Ability.randoability4] << std::endl;
	std::cout << "Ability Choice 5: " << Ability.RandoAbilityList[Ability.randoability5] << std::endl;
	std::cout << "Ability Choice 6: " << Ability.RandoAbilityList[Ability.randoability6] << std::endl;

	std::cout << "\nYour 1st ability choice: " << std::endl;

	std::cin >> Ability.abilityans1;

	//ability choice 1
	while (Ability.abilityans1 < 1 || Ability.abilityans1 > 6)
	{
		std::cout << "invalid input, please choose from the given choices" << std::endl;
		std::cin >> Ability.abilityans1;
	}

	if (Ability.abilityans1 == 1)
	{
		Ability.RandoAbilityBools[Ability.randoability1] = true;
	}
	if (Ability.abilityans1 == 2)
	{
		Ability.RandoAbilityBools[Ability.randoability2] = true;
	}
	if (Ability.abilityans1 == 3)
	{
		Ability.RandoAbilityBools[Ability.randoability3] = true;
	}
	if (Ability.abilityans1 == 4)
	{
		Ability.RandoAbilityBools[Ability.randoability4] = true;
	}
	if (Ability.abilityans1 == 5)
	{
		Ability.RandoAbilityBools[Ability.randoability5] = true;
	}
	if (Ability.abilityans1 == 6)
	{
		Ability.RandoAbilityBools[Ability.randoability6] = true;
	}

	//ability choice 2
	std::cout << "\nYour 2nd ability choice: " << std::endl;

	std::cin >> Ability.abilityans2;

	while (Ability.abilityans2 < 1 || Ability.abilityans2 > 6 || Ability.abilityans2 == Ability.abilityans1)
	{
		std::cout << "invalid input or same ability chose, please re-pick" << std::endl;
		std::cin >> Ability.abilityans2;
	}

	if (Ability.abilityans2 == 1)
	{
		Ability.RandoAbilityBools[Ability.randoability1] = true;
	}
	if (Ability.abilityans2 == 2)
	{
		Ability.RandoAbilityBools[Ability.randoability2] = true;
	}
	if (Ability.abilityans2 == 3)
	{
		Ability.RandoAbilityBools[Ability.randoability3] = true;
	}
	if (Ability.abilityans2 == 4)
	{
		Ability.RandoAbilityBools[Ability.randoability4] = true;
	}
	if (Ability.abilityans2 == 5)
	{
		Ability.RandoAbilityBools[Ability.randoability5] = true;
	}
	if (Ability.abilityans2 == 6)
	{
		Ability.RandoAbilityBools[Ability.randoability6] = true;
	}
}

//NEW CODE TESTING, CLASS SPECIFIC ABILITIES HERE
//DONT TOUCH FOR NOW
void Game::CastClassAbility(int classAbilityChoice, char direction)
{
	int dirRow, dirCol;

	if (!player->PlayerAbilityDirection(direction, dirRow, dirCol))
	{
		return;
	}

	int classAbilityID;

	switch (classAbilityChoice)
	{
	case 1: classAbilityID = Abilities::HEROS_LIGHT; break;
	case 2: classAbilityID = Abilities::SWORVANT; break;
	case 3: classAbilityID = Abilities::SWORVANT_SACRIFICE; break;
	case 4: classAbilityID = Abilities::MAGIC_MISSILE; break;
	case 5: classAbilityID = Abilities::CATCLYSM; break;
	case 6: classAbilityID = Abilities::ICICLE_SPEAR; break;
	case 7: classAbilityID = Abilities::MAGIC_ARROW; break;
	case 8: classAbilityID = Abilities::BULLSEYE; break;
	case 9: classAbilityID = Abilities::PHOENIX_ARROW; break;
	default:
		cout << "Invalid ability." << endl;
		return;
	}

	int abilityRangeMin = Ability.GetMinClsAbiRange(classAbilityID);
	int abilityRangeMax = Ability.GetMaxClsAbiRange(classAbilityID);

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
				switch (classAbilityChoice)
				{
				case 1:
				{
					Ability.HerosLight(*enemy[i], *player); cout << R"("Grant me power, for I shall rid this world of evil and strike my enemies down with the light!")" << "\n" <<
					player->getName() << " casts Hero's Light on " << enemy[i]->getName() << " and " << player->getName() << " heals 8 HP!" << endl; break;
				}
				case 2:
				{
					Ability.Sworvant(*enemy[i]); cout << R"("Behold! For this is the pinnacle of sword fighting. Go forth, "Solvora", and help me clear those in my way!")" << "\n" <<
					player->getName() << " casts Sworvant on " << enemy[i]->getName() << endl; break;
				}
				case 3:
				{
					Ability.SworvantSacrifice(*enemy[i], *player); cout << R"("Just this once, lend my your strength, and in turn, I give a part of my life!")" << "\n" <<
					player->getName() << " casts Sworvant Sacrifice on " << enemy[i]->getName() << " and " << player->getName() << " sacrifices 15 HP!" << enemy[i]->getName() << endl; break;
				}
				case 4:
				{
					Ability.MagicMissile(*enemy[i]); cout << player->getName() << " casts Magic Missile on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 5:
				{
					Ability.Cataclysm(*enemy[i]); cout << R"("Foretold are tales of death, end shall come.")" << "\n" <<
					R"("Borrowing a power from the times of suffering, I cast death upon those who stand against me.")" << "\n" << 
					R"("Forgive me for I use powers that are forbidden...")" << "\n" <<
					player->getName() << " casts Cataclysm on " << enemy[i]->getName() << endl; break;
				}
				case 6:
				{
					Ability.IcicleSpear(*enemy[i]); cout << player->getName() << " casts Icicle Spear on " << enemy[i]->getName() << " and " << player->getName() << " sacrifices 10 HP!" << endl; break;
				}
				case 7:
				{
					Ability.MagicArrow(*enemy[i]); cout << player->getName() << " casts Magic Arrow on " << enemy[i]->getName() << endl; break;
				}
				case 8:
				{
					Ability.Bullseye(*enemy[i]); cout << player->getName() << " casts Bullseye on " << enemy[i]->getName() << "!" << endl; break;
				}
				case 9:
				{
					Ability.PhoenixArrow(*enemy[i], *player); cout << R"("Draw on the flaming bow, as the flaming arrow burns my arm.")" << "\n" <<
					R"("Let the arrow fly as far and high as a Phoenix. Burn my enemies with the flames of life!")" << "\n" <<
					player->getName() << " casts Phoenix Arrow on " << enemy[i]->getName() << " and " << player->getName() << " sacrifices 9 HP!" << enemy[i]->getName() << endl; break;
				}
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