#pragma once
#include "GameScene.h"

#include "Player.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"

#include "Event.h"
#include "Enemy.h"

#include "Abilities.h"

#include "Slime.h"
#include "Goblin.h"
#include "WildBoar.h"
#include "ValSwordman.h"
#include "ValEnforcer.h"
#include "ValArcher.h"

class Game
{
	bool gameRunning;
	char mapGrid[12][12];

	Event event;

	Player* player;

	static const int MAX_ENEMIES = 10;

	Enemy* enemy[MAX_ENEMIES];
	int enemyCount;

	static const int ENEMY_FOREST = 3;
	static const int ENEMY_VILLAGE = 3;
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

	void DisplayEnemyHP(Enemy* enemy);
	int RandNumber(int min, int max);

	void LoadScene(char sym, int sceneNumber);
	void ClearEnemies();
	void CheckSceneExit(char sym);

	// Resolves one ability cast: scans tiles in the chosen direction (range 1-3),
	// applies the matching Ability function to the first enemy found.
	void CastAbility(int abilityChoice, char direction);

	// Applies active damage-over-time effects to enemies once per turn.
	void TickEnemyDoT();

	// TEST CODE FOR ABILITY PICKER RANDOMISER
	void randomAbilityPicker();

	//TEST CODE CLASS ABILITY
	void CastClassAbility(int classAbilityChoice, char direction);
};
