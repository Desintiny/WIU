#pragma once
#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];
	Player* player;

public:
	Game();
	~Game();

	void Start();
	void MainMenu();
	void ClassSelection();
	void DisplayGame();
};
