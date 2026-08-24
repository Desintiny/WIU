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
			else if (input == '2')
			{
				cout << "\n--- Abilities ---" << endl;

				cout << "[1] Fireball (rng "
					<< Ability.GetMinRange(Abilities::FIREBALL) << "-"
					<< Ability.GetMaxRange(Abilities::FIREBALL) << ")  ";

				cout << "[2] Magic Missile (rng "
					<< Ability.GetMinRange(Abilities::MAGIC_MISSILE) << "-"
					<< Ability.GetMaxRange(Abilities::MAGIC_MISSILE) << ")  ";

				cout << "[3] Blood Pierce (rng "
					<< Ability.GetMinRange(Abilities::BLOOD_PIERCE) << "-"
					<< Ability.GetMaxRange(Abilities::BLOOD_PIERCE) << ")" << endl;

				cout << "[4] Icicle Spear (rng "
					<< Ability.GetMinRange(Abilities::ICICLE_SPEAR) << "-"
					<< Ability.GetMaxRange(Abilities::ICICLE_SPEAR) << ")  ";

				cout << "[5] Lightning Bolt (rng "
					<< Ability.GetMinRange(Abilities::LIGHTNING_BOLT) << "-"
					<< Ability.GetMaxRange(Abilities::LIGHTNING_BOLT) << ")  ";

				cout << "[6] Blood Bomb (rng "
					<< Ability.GetMinRange(Abilities::BLOOD_BOMB) << "-"
					<< Ability.GetMaxRange(Abilities::BLOOD_BOMB) << ")" << endl;

				cout << "[7] Poison Shot (rng "
					<< Ability.GetMinRange(Abilities::POISON_SHOT) << "-"
					<< Ability.GetMaxRange(Abilities::POISON_SHOT) << ")  ";

				cout << "[8] Air Cutter (rng "
					<< Ability.GetMinRange(Abilities::AIR_CUTTER) << "-"
					<< Ability.GetMaxRange(Abilities::AIR_CUTTER) << ")  ";

				cout << "[9] Boulder Throw (rng "
					<< Ability.GetMinRange(Abilities::BOULDER_THROW) << "-"
					<< Ability.GetMaxRange(Abilities::BOULDER_THROW) << ")" << endl;

				cout << "[0] Water Bolt (rng "
					<< Ability.GetMinRange(Abilities::WATER_BOLT) << "-"
					<< Ability.GetMaxRange(Abilities::WATER_BOLT) << ")" << endl;

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
				// Show the next story
				StoryDialogue();

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
				// Show the next story
				StoryDialogue();

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
				// Show the final story
				StoryDialogue();

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
	ifstream inputFile("Story.txt");

	if (!inputFile.is_open())
	{
		cout << "Unable to open Story.txt!" << endl;
		return;
	}

	int storyNumber = loopCount + 1;

	string storyTitle = "======Story " + to_string(storyNumber) + "======";

	string line;
	bool printingStory = false;

	cout << "\n=====================================\n";

	while (getline(inputFile, line))
	{
		// Find the correct story
		if (line == storyTitle)
		{
			printingStory = true;
			continue;
		}

		// Stop when we reach the next story
		if (printingStory && line.find("======Story ") == 0)
		{
			break;
		}

		// Print the story
		if (printingStory)
		{
			cout << line << endl;
		}
	}

	cout << "=====================================\n";

	cout << "\nPress any key to continue...";
	_getch();

	system("cls");

	inputFile.close();
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
		cout << STYLE_PURPLE << "ENEMY (E)";
	}
	cout << endl;

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

		cout << "] ";
	}
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

	cout << "\n[WASD] Move | [IJKL] Attack | [2] Abilities | [E] Inventory" << endl;
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

		enemyCount = ENEMY_FOREST;

		enemy[0] = new Slime("Slime");
		SpawnEntity(enemy[0], 'S', 2, 8);

		enemy[1] = new Goblin("Goblin");
		SpawnEntity(enemy[1], 'G', 6, 8);
	}
	// ------------------------- VILLAGE -------------------------
	else if (sceneNumber == 2)
	{
		SpawnEntity(player, sym, 4, 1);

		enemyCount = ENEMY_VILLAGE;

		enemy[0] = new ValArcher("Valdrek Archer");
		SpawnEntity(enemy[0], 'A', 2, 8);

		enemy[1] = new ValSwordman("Valdrek Swordsman");
		SpawnEntity(enemy[1], 'S', 4, 8);

		enemy[2] = new ValEnforcer("Valdrek Enforcer");
		SpawnEntity(enemy[2], 'E', 6, 8);

		enemy[3] = new WildBoar("Wild Boar");
		SpawnEntity(enemy[3], 'W', 8, 8);
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

	// Convert the menu choice to the matching private range entry
	// stored inside Abilities.
	int abilityId;

	switch (abilityChoice)
	{
	case 1: abilityId = Abilities::FIREBALL; break;
	case 2: abilityId = Abilities::MAGIC_MISSILE; break;
	case 3: abilityId = Abilities::BLOOD_PIERCE; break;
	case 4: abilityId = Abilities::ICICLE_SPEAR; break;
	case 5: abilityId = Abilities::LIGHTNING_BOLT; break;
	case 6: abilityId = Abilities::BLOOD_BOMB; break;
	case 7: abilityId = Abilities::POISON_SHOT; break;
	case 8: abilityId = Abilities::AIR_CUTTER; break;
	case 9: abilityId = Abilities::BOULDER_THROW; break;
	case 0: abilityId = Abilities::WATER_BOLT; break;
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
