#pragma once
#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

#include "Inventory.h"

#include "Event.h"
#include "Event2.h"

#include "Enemy.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];
	Player* player;
	Inventory inventory;

	static const int NUM_ENEMY = 8;
	Enemy* enemy[NUM_ENEMY];

public:
	Game();
	~Game();

	void Start();
	void SpawnEntity(Entity* entity, char sym, int row, int col);
	void MainMenu();
	char ClassSelection(void);
	void DisplayGame(char sym);

	void Story();
	void PathChoice();
};
