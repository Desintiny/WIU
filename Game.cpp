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

// ============================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================

Game::Game()
{
	gameRunning = true;
	player = nullptr;
	enemyCount = 0;

	loopCount = 0;
	maxLoops = 6;


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

// ============================================================
// MAIN GAME FLOW
// ============================================================

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

	// Pick 2 starter abilities from the shared ability pool.
	randomAbilityPicker();

	// ------- SPAWN PLAYER AT THE LEFT SIDE OF THE MAP -------
	if (player != nullptr)
	{
		event.PathChoice(player);

		cout << "\nPress any key to continue...";
		(void)_getch();

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

			//// -------------- for debugging --------------
			//if (input == '0')
			//{
			//	system("cls");

			//	Boss boss("Emperor Valdrek");

			//	bool isBadEnding = false;

			//	if (!isBadEnding)
			//	{
			//		boss.StartBossFight(player, Ability);
			//	}
			//	else
			//	{
			//		gameRunning = false;
			//	}
			//}
			//// -------------- for debugging --------------

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
				(void)_getch();
			}

			// -------- ABILITIES --------
			else if (input == '2')
			{
				cout << "\n--- Abilities ---" << endl;
				cout << "Stamina: " << player->getStamina() << "/" << player->getMaxStamina() << endl;

				// Menu slots are separate from the real ability IDs.
				// This means the first unlocked ability is always [1], the second is [2], etc.
				int abilitySlots[9];
				int slotCount = 0;

				for (int id = 1; id <= 9; id++)
				{
					if (Ability.RandoAbilityBools[id])
					{
						abilitySlots[slotCount] = id;

						cout << "[" << slotCount + 1 << "] " << Ability.RandoAbilityList[id]
							<< " (rng " << Ability.GetMinRange(id) << "-" << Ability.GetMaxRange(id)
							<< ", ST " << Ability.GetStaminaCost(id) << ")" << endl;

						slotCount++;
					}
				}

				char abilityChoice = _getch();
				int selectedSlot = abilityChoice - '1';

				if (selectedSlot >= 0 && selectedSlot < slotCount)
				{
					// Translate the menu slot back into the real ability ID.
					int abilityIndex = abilitySlots[selectedSlot];

					cout << "\nInput a Direction [IJKL]: " << endl;
					char abilityDirection = _getch();
					if (abilityDirection == 'i' || abilityDirection == 'j' ||
						abilityDirection == 'k' || abilityDirection == 'l' ||
						abilityDirection == 'I' || abilityDirection == 'J' ||
						abilityDirection == 'K' || abilityDirection == 'L')
					{
						CastAbility(abilityIndex, abilityDirection);
					}
				}
				else
				{
					cout << "\nInvalid ability choice." << endl;
				}

				if (!encounterFinished && gameRunning)
				{
					cout << "\nPress any key to continue...";
					(void)_getch();
				}
			}

			// -------- CLASS ABILITIES --------
			else if (input == 'q' || input == 'Q')
			{
				cout << "\n--- Class Abilities ---" << endl;
				cout << "Stamina: " << player->getStamina() << "/" << player->getMaxStamina() << endl;

				for (int id = 1; id <= 9; id++)
				{
					cout << "[" << id << "] " << Ability.ClassAbilityList[id]
						<< " (rng " << Ability.GetMinClsAbiRange(id) << "-" << Ability.GetMaxClsAbiRange(id)
						<< ", ST " << Ability.GetClassStaminaCost(id) << ")" << endl;
				}

				char abilityChoice = _getch();
				if (abilityChoice >= '1' && abilityChoice <= '9')
				{
					cout << "\nInput a Direction [IJKL]: " << endl;
					char abilityDirection = _getch();
					if (abilityDirection == 'i' || abilityDirection == 'j' ||
						abilityDirection == 'k' || abilityDirection == 'l' ||
						abilityDirection == 'I' || abilityDirection == 'J' ||
						abilityDirection == 'K' || abilityDirection == 'L')
					{
						CastClassAbility(abilityChoice - '0', abilityDirection);
					}
				}

				if (!encounterFinished && gameRunning)
				{
					cout << "\nPress any key to continue...";
					(void)_getch();
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


									if (AreAllEnemiesDead())
									{
										if (scene.getCurrentScene() == 1 ||
											scene.getCurrentScene() == 2)
										{
											CompleteCombat();
										}
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
						int distance =
							abs(enemy[i]->getRow() - player->getRow()) +
							abs(enemy[i]->getCol() - player->getCol());

						bool besidePlayer = (distance == 1);

						if (enemy[i]->getRecovering())
						{
							cout << enemy[i]->getName()
								<< " is recovering." << endl;

							enemy[i]->setRecovering(false);
						}
						else if (besidePlayer)
						{
							enemy[i]->EnemyAttack(player);

							// Thorns can defeat the attacking enemy. Remove it immediately.
							if (!enemy[i]->IsAlive())
							{
								mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';
								delete enemy[i];
								enemy[i] = nullptr;

								if (AreAllEnemiesDead())
								{
									if (scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2)
									{
										CompleteCombat();
									}
								}
							}
							else
							{
								enemy[i]->setRecovering(true);
							}
						}
						else
						{
							enemy[i]->EnemyMovement(player, mapGrid);
						}
					}
				}

				if (!player->IsAlive())
				{
					GameOver();
					return;
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
					(void)_getch();

					system("cls");

					Boss* boss = nullptr;
					boss = new Boss("Emperor Valdrek");
					bool isBadEnding = boss->DisplayCutscene();

					if (!isBadEnding)
					{
						bool winGame = boss->StartBossFight(player, Ability);

						if (winGame)
						{
							VictoryScreen();
						}
						else
						{
							GameOver();
						}
					}
					else
					{
						GameOver();
					}

					delete boss;
					boss = nullptr;

					gameRunning = false;
				}
			}

			// Clears the the rest of the console text, so it doesn't show the previous map
			system("cls");
		}
	}
}

void Game::MainMenu()
{
	int option;

	do
	{
		cout << "============= HAVENFALL =============" << endl;
		cout << "	   1. Start Game" << endl;
		cout << "	   2. Quit Game" << endl;
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

void Game::StoryDialogue()
{
	ifstream inputFile("Story.txt");

	if (!inputFile.is_open())
	{
		cout << "Unable to open Story.txt!" << endl;
		return;
	}

	// Story 1 when loopCount is 0,
	// Story 2 when loopCount is 1, etc.
	int storyNumber = loopCount + 1;

	string storyTitle = "======Story " + to_string(storyNumber) + "======";

	string line;
	bool printingStory = false;

	cout << "\n=====================================\n";

	while (getline(inputFile, line))
	{
		// Find the story we want
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

		// Print the lines belonging to this story
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

void Game::GameOver()
{
	system("cls");

	cout << "=====================================\n";
	cout << "              GAME OVER              \n";
	cout << "=====================================\n\n";

	cout << player->getName()
		<< " has been defeated!\n\n";

	cout << "You reached:\n";

	if (loopCount < 3)
	{
		cout << "Forest\n";
	}
	else if (loopCount < 6)
	{
		cout << "Village\n";
	}
	else
	{
		cout << "Final Boss\n";
	}

	cout << "\nEncounters completed: "
		<< loopCount
		<< endl;

	cout << "\n=====================================\n";
	cout << "Press any key to return to menu...";
	_getch();

	system("cls");

	gameRunning = false;
}

void Game::VictoryScreen()
{
	system("cls");

	cout << "=====================================\n";
	cout << "              VICTORY!               \n";
	cout << "=====================================\n\n";

	cout << "Valdrek has been defeated!\n";
	cout << "Havenbrook is finally free.\n\n";

	cout << player->getName()
		<< " has completed the journey!\n";

	cout << "\nEncounters completed: "
		<< loopCount
		<< endl;

	cout << "\n=====================================\n";
	cout << "       THANK YOU FOR PLAYING!        \n";
	cout << "=====================================\n";

	cout << "\nPress any key to exit...";
	_getch();

	gameRunning = false;
}

// ============================================================
// DISPLAY / UI
// ============================================================

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

	// ------------ PLAYER UI ------------

	cout << STYLE_ORANGE << "YOU (" << sym << ")			";
	cout << endl;

	// ------------ PLAYER HEALTH ------------

	cout << STYLE_RED << "HP [";

	for (int i = 0; i < 10; i++)
	{
		cout << healthBar[i];
	}

	cout << "] " << player->getHealth() << '/' << displayHealth << "	";
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

	// ------------ DAMAGE OVER TIME / STATUS MESSAGE ------------

	if (!dotMessage.empty())
	{
		cout << "\n--- STATUS EFFECTS ---" << endl;
		cout << dotMessage;
	}

	cout << "\n[WASD] Move | [IJKL] Attack | [2] Abilities | [Q] Class Abilities | [E] Inventory" << endl;
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

// ============================================================
// SCENE / PROGRESSION
// ============================================================

void Game::SpawnEntity(Entity* entity, char sym, int row, int col)
{
	entity->setRow(row);
	entity->setCol(col);
	mapGrid[row][col] = sym;
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

bool Game::AreAllEnemiesDead()
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			return false;
		}
	}

	return true;
}

void Game::CompleteCombat()
{
	loopCount++;
	system("cls");

	// ---------------- HEAL PLAYER ----------------
	int healthBefore = player->getHealth();

	// Heal 25% of max HP after a normal encounter
	int healAmount = player->getMaxHealth() / 4;

	int newHealth = player->getHealth() + healAmount;

	if (newHealth > player->getMaxHealth())
	{
		newHealth = player->getMaxHealth();
	}

	player->setHealth(newHealth);

	int actualHealing = player->getHealth() - healthBefore;

	// ---------------- RESTORE STAMINA ----------------
	player->setStamina(player->getMaxStamina());

	// ---------------- DISPLAY ----------------
	cout << "\nEncounter completed!";

	cout << "\nYou recovered "
		<< actualHealing
		<< " HP!";

	cout << "\nHP: "
		<< player->getHealth()
		<< "/"
		<< player->getMaxHealth();

	cout << "\nStamina: "
		<< player->getStamina()
		<< "/"
		<< player->getMaxStamina();

	cout << "\nProgress: "
		<< loopCount
		<< "/"
		<< maxLoops;

	encounterFinished = true;
}

// ============================================================
// STATUS EFFECTS
// ============================================================

void Game::TickEnemyDoT()
{
	// Clear the previous turn's DoT text.
	// New DoT text will be stored here and displayed by DisplayGame().
	dotMessage.clear();

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

			int dotDamage = healthBefore - enemy[i]->getHealth();

			dotMessage +=
				enemy[i]->getName()
				+ " takes "
				+ to_string(dotDamage)
				+ " damage from a damage-over-time effect!\n";

			if (enemy[i]->IsAlive())
			{
				dotMessage +=
					enemy[i]->getName()
					+ " has "
					+ to_string(enemy[i]->getHealth())
					+ " HP left.\n";
			}
			else
			{
				dotMessage +=
					enemy[i]->getName()
					+ " has been defeated by the damage-over-time effect!\n";

				mapGrid[enemy[i]->getRow()][enemy[i]->getCol()] = '.';

				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	// If DoT killed an enemy, check whether that was the final enemy.
	if (anyDotDamage)
	{
		if (AreAllEnemiesDead())
		{
			if (scene.getCurrentScene() == 1 ||
				scene.getCurrentScene() == 2)
			{
				CompleteCombat();
			}
		}
	}

	// No _getch() or system("cls") here.
	// DisplayGame() will show dotMessage on the normal main screen.
}

// ============================================================
// ABILITY / TARGETING
// ============================================================

Enemy* Game::FindEnemyInRange(int minRange, int maxRange, int dirRow, int dirCol)
{
	for (int dist = minRange; dist <= maxRange; dist++)
	{
		int checkRow =
			player->getRow() + (dirRow * dist);

		int checkCol =
			player->getCol() + (dirCol * dist);

		for (int i = 0; i < enemyCount; i++)
		{
			if (enemy[i] != nullptr &&
				enemy[i]->getRow() == checkRow &&
				enemy[i]->getCol() == checkCol)
			{
				return enemy[i];
			}
		}
	}

	return nullptr;
}

void Game::CastAbility(int abilityChoice, char direction)
{
	int dirRow = 0;
	int dirCol = 0;

	if (!player->PlayerAbilityDirection(direction, dirRow, dirCol))
	{
		cout << "\nInvalid direction!" << endl;
		return;
	}

	if (abilityChoice < 1 || abilityChoice > 9 || !Ability.RandoAbilityBools[abilityChoice])
	{
		cout << "\nInvalid or locked ability!" << endl;
		return;
	}

	int staminaCost = Ability.GetStaminaCost(abilityChoice);
	if (player->getStamina() < staminaCost)
	{
		cout << "\nNot enough stamina! Required: " << staminaCost << " ST" << endl;
		return;
	}

	// Blood Pierce can hit up to 2 enemies in a straight line and costs 5 HP once.
	if (abilityChoice == Abilities::BLOOD_PIERCE)
	{
		int enemyHits = 0;
		const int maxTargets = 2;

		for (int dist = Ability.GetMinRange(abilityChoice);
			dist <= Ability.GetMaxRange(abilityChoice) && enemyHits < maxTargets; dist++)
		{
			int checkRow = player->getRow() + (dirRow * dist);
			int checkCol = player->getCol() + (dirCol * dist);

			for (int i = 0; i < enemyCount; i++)
			{
				if (enemy[i] != nullptr && enemy[i]->getRow() == checkRow && enemy[i]->getCol() == checkCol)
				{
					Ability.BloodPierce(*enemy[i]);
					cout << player->getName() << " casts Blood Pierce on " << enemy[i]->getName() << "!" << endl;

					if (!enemy[i]->IsAlive())
					{
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
			cout << player->getName() << " casts Blood Pierce at empty space. No enemy there." << endl;
			return;
		}

		player->setStamina(player->getStamina() - staminaCost);
		player->TakeDamage(5);
	}
	else
	{
		Enemy* target = FindEnemyInRange(
			Ability.GetMinRange(abilityChoice),
			Ability.GetMaxRange(abilityChoice),
			dirRow,
			dirCol);

		if (target == nullptr)
		{
			cout << "\n" << player->getName() << " casts the ability at empty space. No enemy there." << endl;
			return;
		}

		player->setStamina(player->getStamina() - staminaCost);

		switch (abilityChoice)
		{
		case Abilities::FIREBALL:
			Ability.Fireball(*target); break;
		case Abilities::BOULDER_THROW:
			Ability.BoulderThrow(*target); break;
		case Abilities::POISON_SHOT:
			Ability.PoisonShot(*target); break;
		case Abilities::LIGHTNING_BOLT:
			Ability.LightningBolt(*target); break;
		case Abilities::BLOOD_BOMB:
			Ability.BloodBomb(*target, *player); break;
		case Abilities::WATER_BOLT:
			Ability.WaterBolt(*target, *player); break;
		case Abilities::AIR_CUTTER:
			Ability.Aircutter(*target); break;
		case Abilities::BLOOMING_FLOWER:
			Ability.BloomingFlowers(*target, *player); break;
		}

		cout << player->getName() << " casts " << Ability.RandoAbilityList[abilityChoice]
			<< " on " << target->getName() << "!" << endl;

		if (target->IsAlive())
		{
			cout << target->getName() << " has " << target->getHealth() << " HP left." << endl;
		}
		else
		{
			cout << target->getName() << " has been defeated!" << endl;
			mapGrid[target->getRow()][target->getCol()] = '.';
			for (int i = 0; i < enemyCount; i++)
			{
				if (enemy[i] == target)
				{
					delete enemy[i];
					enemy[i] = nullptr;
					break;
				}
			}
		}
	}

	cout << "Stamina remaining: " << player->getStamina() << "/" << player->getMaxStamina() << " ST" << endl;

	if (!player->IsAlive())
	{
		GameOver();
		return;
	}

	if (AreAllEnemiesDead())
	{
		if (scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2)
		{
			CompleteCombat();
		}
	}
}



void Game::randomAbilityPicker()
{
	int picks[6];
	for (int i = 0; i < 6; i++)
	{
		bool unique;
		do
		{
			picks[i] = (rand() % 9) + 1;
			unique = true;
			for (int j = 0; j < i; j++)
			{
				if (picks[i] == picks[j]) unique = false;
			}
		} while (!unique);
	}

	cout << "Pick 2 out of these 6 abilities\n";
	cout << "These will be your starter abilities.\n";
	for (int i = 0; i < 6; i++)
	{
		cout << "[" << (i + 1) << "] " << Ability.RandoAbilityList[picks[i]] << endl;
	}

	int firstChoice;
	int secondChoice;
	cout << "\nYour 1st ability choice: ";
	cin >> firstChoice;
	while (firstChoice < 1 || firstChoice > 6)
	{
		cout << "Invalid input. Choose 1-6: ";
		cin >> firstChoice;
	}

	cout << "Your 2nd ability choice: ";
	cin >> secondChoice;
	while (secondChoice < 1 || secondChoice > 6 || secondChoice == firstChoice)
	{
		cout << "Invalid or duplicate choice. Choose again: ";
		cin >> secondChoice;
	}

	Ability.RandoAbilityBools[picks[firstChoice - 1]] = true;
	Ability.RandoAbilityBools[picks[secondChoice - 1]] = true;
	(void)_getch();
	system("cls");
}

void Game::CastClassAbility(int classAbilityChoice, char direction)
{
	int dirRow = 0;
	int dirCol = 0;
	if (!player->PlayerAbilityDirection(direction, dirRow, dirCol)) return;
	if (classAbilityChoice < 1 || classAbilityChoice > 9) return;

	int staminaCost = Ability.GetClassStaminaCost(classAbilityChoice);
	if (player->getStamina() < staminaCost)
	{
		cout << "\nNot enough stamina! Required: " << staminaCost << " ST" << endl;
		return;
	}

	Enemy* target = FindEnemyInRange(
		Ability.GetMinClsAbiRange(classAbilityChoice),
		Ability.GetMaxClsAbiRange(classAbilityChoice),
		dirRow,
		dirCol);

	if (target == nullptr)
	{
		cout << player->getName() << " casts at empty space. No enemy there." << endl;
		return;
	}

	player->setStamina(player->getStamina() - staminaCost);

	switch (classAbilityChoice)
	{
	case Abilities::HEROS_LIGHT: Ability.HerosLight(*target, *player); break;
	case Abilities::SWORVANT: Ability.Sworvant(*target); break;
	case Abilities::SWORVANT_SACRIFICE: Ability.SworvantSacrifice(*target, *player); break;
	case Abilities::MAGIC_MISSILE: Ability.MagicMissile(*target); break;
	case Abilities::CATCLYSM: Ability.Cataclysm(*target); break;
	case Abilities::ICICLE_SPEAR: Ability.IcicleSpear(*target); break;
	case Abilities::MAGIC_ARROW: Ability.MagicArrow(*target); break;
	case Abilities::BULLSEYE: Ability.Bullseye(*target); break;
	case Abilities::PHOENIX_ARROW: Ability.PhoenixArrow(*target, *player); break;
	}

	cout << player->getName() << " casts " << Ability.ClassAbilityList[classAbilityChoice]
		<< " on " << target->getName() << "!" << endl;
	cout << "Stamina remaining: " << player->getStamina() << "/" << player->getMaxStamina() << " ST" << endl;

	if (!player->IsAlive())
	{
		GameOver();
		return;
	}

	if (!target->IsAlive())
	{
		cout << target->getName() << " has been defeated!" << endl;
		mapGrid[target->getRow()][target->getCol()] = '.';
		for (int i = 0; i < enemyCount; i++)
		{
			if (enemy[i] == target)
			{
				delete enemy[i];
				enemy[i] = nullptr;
				break;
			}
		}
	}

	if (AreAllEnemiesDead())
	{
		if (scene.getCurrentScene() == 1 || scene.getCurrentScene() == 2)
		{
			CompleteCombat();
		}
	}
}
