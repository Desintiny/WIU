#include "Enemy.h"

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
