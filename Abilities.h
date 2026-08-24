#pragma once
#include "Entity.h"
class Abilities
{
public:
	//any ability names goes here
	//declare any ability like this void ABILITYNAME(Entity& target)

	//Direct DMG
	void LightningBolt(Entity& target);
	void MagicMissile(Entity& target);
	void WaterBolt(Entity& target);
	void BoulderThrow(Entity& target);
	void Aircutter(Entity& target);

	//DoT
	void Fireball(Entity& target);
	void IcicleSpear(Entity& target);
	void PoisonShot(Entity& target);

	//Resource Tradeoff
	void BloodPierce(Entity& target, Entity& caster);
	void BloodBomb(Entity& target, Entity& caster);
};

