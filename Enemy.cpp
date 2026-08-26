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

	disabledTurns = 0;
}

Enemy::~Enemy()
{

}
int Enemy::GetDisabledTurns()
{
	return disabledTurns;
}

void Enemy::SetDisabledTurns(int turns)
{
	disabledTurns = turns;
}
void Enemy::EnemyAttack(Entity* target)
{
	if (target != nullptr)
	{
		if (disabledTurns > 0)
		{
			cout << getName() << " is unable to attack!" << endl;
			disabledTurns--;
			return;
		}
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
		if (player != nullptr)
		{
			if (player->GetDisableTurns() > 0)
			{
				disabledTurns = player->GetDisableTurns();

				cout << getName()
					<< " has been disabled for "
					<< disabledTurns
					<< " turns!" << endl;
			}
		}
		if (player != nullptr)
		{
			rng.Thorns(player->GetThornsChance());

			if (rng.GetThorns())
			{
				TakeDamage(dmg);

				cout << getName() << " takes "
					<< dmg << " reflected damage!" << endl;
			}
		}
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
