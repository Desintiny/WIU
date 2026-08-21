#include "Entity.h"

Entity::Entity(string n)
{
	name = n;

	healthPts = 0;
	maxHealthPts = 0;

	attackPts = 0;

	row = 0;
	col = 0;
}

Entity::~Entity()
{

}

void Entity::setName(string n)
{
	name = n;
}

string Entity::getName(void)
{
	return name;
}

void Entity::setHealth(int h)
{
	healthPts = h;
}

int Entity::getHealth(void)
{
	return healthPts;
}

void Entity::setMaxHealth(int h)
{
	maxHealthPts = h;
}

int Entity::getMaxHealth(void)
{
	return maxHealthPts;
}

void Entity::setAttack(int s)
{
	attackPts = s;
}

int Entity::getAttack(void)
{
	return attackPts;
}

void Entity::TakeDamage(int amount)
{
	healthPts -= amount;
	if (healthPts < 0)
		healthPts = 0;
}

bool Entity::IsAlive(void)
{
	return healthPts > 0;
}

void Entity::setRow(int r)
{
	row = r;
}

int Entity::getRow(void)
{
	return row;
}

void Entity::setCol(int c)
{
	col = c;
}

int Entity::getCol(void)
{
	return col;
}

//alonso test code
void Entity::SetDoT(int Damage, int Turns)
{
	DoTDamage = Damage;
	DoTTurnRemain = Turns;
}

void Entity::TickDoT() //the dmg ticking
{
	if (DoTTurnRemain > 0)
	{
		TakeDamage(DoTDamage);
		DoTTurnRemain--;
	}
}