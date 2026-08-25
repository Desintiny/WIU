#include "Enemy.h"
#include "Player.h"
#include "RNG.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(string n) : Entity(n)
{
	// baseline stats so enemies aren't a 1-hit kill (Entity defaults everything to 0 otherwise)
	setHealth(18);
	setMaxHealth(18);
	setAttack(5);
}

Enemy::~Enemy()
{

}
void Enemy::EnemyAttack(Entity* target)
{
	if (target != nullptr)
	{
		RNG rng;
		Player* player = dynamic_cast<Player*>(target);

		if (player != nullptr)
		{
			rng.Dodge(player->getDodgeChance());

			if (rng.GetDodged())
			{
				return;
			}
		}

		int dmg = getAttack();

		target->TakeDamage(dmg);

		cout << getName() << " attacks " << target->getName()
			<< " for " << dmg << " damage!" << endl;

		if (!target->IsAlive())
		{
			cout << target->getName() << " has been defeated!" << endl;
		}
		else
		{
			cout << target->getName() << " has "
				<< target->getHealth() << " HP left." << endl;
		}
	}
}
