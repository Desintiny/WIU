#pragma once
#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

#include "Event.h"
#include "Enemy.h"

//test
#include "Abilities.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];
	Player* player;

	static const int NUM_ENEMY = 8;
	Event event;
	Enemy* enemy[NUM_ENEMY];

public:
	Game();
	~Game();

	void Start();
	void SpawnEntity(Entity* entity, char sym, int row, int col);
	void MainMenu();
	char ClassSelection(void);
	void DisplayGame(char sym);

	void StoryDialogue();

	//test
	Abilities Ability;
};
