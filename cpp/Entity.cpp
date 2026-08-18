#include "Entity.h"

Entity::Entity(string n)
{
	name = n;

	healthPts = 0;
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

void Entity::setAttack(int a)
{
	attackPts = a;
}

int Entity::getAttack(void)
{
	return attackPts;
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
