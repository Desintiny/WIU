#include "Player.h"

Player::Player(string n) : Entity(n)
{
	//playerWeapon = nullptr;

	moveBtn[0] = { 'w' };
	moveBtn[1] = { 'a' };
	moveBtn[2] = { 's' };
	moveBtn[3] = { 'd' };

	intDirection[0] = { 'i' };
	intDirection[1] = { 'j' };
	intDirection[2] = { 'k' };
	intDirection[3] = { 'l' };
};

Player::~Player()
{
	//delete playerWeapon;
}

char Player::GetDirection(int i)
{
	return intDirection[i];
}

void Player::PlayerMovement()
{
	//int newRow = getRow(), newCol = getCol();

	//if (m == moveBtn[0]) // W
	//{
	//	newRow = getRow() - 1;
	//}
	//else if (m == moveBtn[1]) // A
	//{
	//	newCol = getCol() - 1;
	//}
	//else if (m == moveBtn[2]) // S
	//{
	//	newRow = getRow() + 1;
	//}
	//else if (m == moveBtn[3]) // D
	//{
	//	newCol = getCol() + 1;
	//}

	//if (map.isWalkable(newRow, newCol))
	//{
	//	map.moveEntity(getRow(), getCol(), newRow, newCol);
	//	setRow(newRow);
	//	setCol(newCol);
	//}
}

void Player::PlayerAttack()
{

}

void Player::EquipWeapon()
{

}