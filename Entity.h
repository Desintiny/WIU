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

	void setRow(int);
	int getRow(void);

	void setCol(int);
	int getCol(void);

	void heal(int amount);
};

