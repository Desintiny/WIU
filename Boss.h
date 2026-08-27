#pragma once
#include "Enemy.h"
#include "Player.h"

#include "Abilities.h"

#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

class Boss : public Enemy
{
	int ImpSlash;
	int DarkExe;
	int EmpWrath;

public:
	Boss(string n);
	~Boss();

	void EnemyMovement(Entity* target, char mapGrid[12][12]);
	void EnemyAttack(Entity* target);

	void setImperialSlash(int);
	int getImperialSlash(void);

	void setDarkExecution(int);
	int getDarkExecution(void);

	void setEmperorWrath(int);
	int getEmperorWrath(void);

	bool StartBossFight(Player* player, Abilities& Ability);
	void BossTurn(Player* player);
	void DisplayBattle(Player* player);

	void DisplayLine(string text);
	void ReadDialog(string section);

	bool DisplayCutscene();

	bool ValdrekOfferDialog();
	bool InitiateFightDialog();
	bool BadEndingDialog();

	void GoodEndingDialog();
};