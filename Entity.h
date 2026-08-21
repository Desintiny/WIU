#pragma once
#include <string>
using namespace std;

class Entity
{
	string name;
	int healthPts, maxHealthPts, attackPts;
	int row, col;

public:
	Entity(string n);
	virtual ~Entity();

	void setName(string);
	string getName(void);

	void setHealth(int);
	int getHealth(void);

	void setMaxHealth(int);
	int getMaxHealth(void);

	void setAttack(int);
	int getAttack(void);

	void TakeDamage(int amount);
	bool IsAlive(void);

	void setRow(int);
	int getRow(void);

	void setCol(int);
	int getCol(void);

	//alonso dot test
	int DoTDamage; //dot damage
	int DoTTurnRemain; //turns for dot

	void SetDoT(int Damage, int Turns); //func to set the dot upon certain ability use
	void TickDoT(); //use to do tick/per turn dmg and not instant

};
