#include "Abilities.h"
#include <iostream>
#include "Entity.h"

/*
build abilities here with this structure
 void Abilities::ABILITYNAME(Entity& target)
 {
	target.TakeDamage(dmg num here) note: dmg is hardcoded
	target.SetDoT(dmg per tick, duration) // so 3, 3 means 3 dmg for 3 turns
 }
*/

//definitions in case
/*
Direct damage -- Only does dmg
DoT -- Has Damage over time as an addition
Resource Tradeoff -- uses a different resource than mp
*/

//Direct Damage Spells
void Abilities::LightningBolt(Entity& target)
{
	target.TakeDamage(2);
}

void Abilities::MagicMissile(Entity& target)
{
	target.TakeDamage(10);
}

void Abilities::WaterBolt(Entity& target)
{
	target.TakeDamage(3);
}

void Abilities::BoulderThrow(Entity& target)
{
	target.TakeDamage(8);
}

void Abilities::Aircutter(Entity& target)
{
	target.TakeDamage(5);
}

//DoT Spells
void Abilities::Fireball(Entity& target)
{
	target.TakeDamage(4);
	target.SetDoT(2, 2); //dmg, turns
}

void Abilities::IcicleSpear(Entity& target)
{
	target.TakeDamage(3);
	target.SetDoT(3, 3);
}

void Abilities::PoisonShot(Entity& target)
{
	target.TakeDamage(3);
	target.SetDoT(2, 5);
}

//Resource Tradeoff Spells

void Abilities::BloodPierce(Entity& target, Entity& caster)
{
	target.TakeDamage(6);

	caster.TakeDamage(5); //casters(player) resource tradeoff, hp in this case
}

void Abilities::BloodBomb(Entity& target, Entity& caster)
{
	target.TakeDamage(10);

	caster.TakeDamage(10); //casters(player) resource tradeoff, hp in this case
}
