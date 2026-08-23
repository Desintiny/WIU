#pragma once
#include "GameScene.h"

#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

#include "Event.h"
#include "Enemy.h"

#include "Abilities.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];

	Event event;

	Player* player;

	static const int MAX_ENEMIES = 10;

	Enemy* enemy[MAX_ENEMIES];
	int enemyCount;

	static const int ENEMY_FOREST = 2;
	static const int ENEMY_VILLAGE = 4;
	static const int ENEMY_BOSS = 1;

	GameScene scene;
	bool exitUnlocked;

	int loopCount;
	int maxLoops;

	bool encounterFinished;

	Abilities Ability;

public:
	Game();
	~Game();

	void Start();
	void StoryDialogue();

	void SpawnEntity(Entity* entity, char sym, int row, int col);
	void MainMenu();
	char ClassSelection(void);
	void DisplayGame(char sym);

	void LoadScene(char sym, int sceneNumber);
	void ClearEnemies();
	void CheckSceneExit(char sym);

	// Resolves one ability cast: scans tiles in the chosen direction (range 1-3),
	// applies the matching Ability function to the first enemy found.
	void CastAbility(int abilityChoice, char direction);
};

