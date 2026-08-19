#pragma once
#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

#include "Enemy.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];
	Player* player;
	Enemy* enemy;

public:
	Game();
	~Game();

	void Start();
	void SpawnEntity(Entity* entity, char sym, int row, int col);
	void MainMenu();
	void ClassSelection();
	void DisplayGame();
};
