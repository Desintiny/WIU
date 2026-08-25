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
	recovering = false;
}

Enemy::~Enemy()
{

}

bool Enemy::getRecovering()
{
	return recovering;
}

void Enemy::setRecovering(bool value)
{
	recovering = value;
}

void Enemy::EnemyAttack(Entity* target)
{
	if (target != nullptr)
	{
		// Player equipment/class dodge chance is checked before damage.
		RNG rng;
		Player* targetPlayer = dynamic_cast<Player*>(target);

		if (targetPlayer != nullptr)
		{
			rng.Dodge(targetPlayer->getDodgeChance());
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
