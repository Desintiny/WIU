#include "Abilities.h"
#include <iostream>
#include "Entity.h"
#include "RNG.h"

using namespace std;


// ============================================================
// DIRECT DAMAGE ABILITIES
// ============================================================

void Abilities::LightningBolt(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(100);

    if (rng.GetDidHit())
    {
        target.TakeDamage(2);
    }
}


void Abilities::MagicMissile(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(85);

    if (rng.GetDidHit())
    {
        target.TakeDamage(10);
    }
}


void Abilities::WaterBolt(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(3);
    }
}


void Abilities::BoulderThrow(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(8);
    }
}


void Abilities::Aircutter(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(5);
    }
}


// ============================================================
// DAMAGE OVER TIME ABILITIES
// ============================================================

void Abilities::Fireball(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(95);

    if (rng.GetDidHit())
    {
        target.TakeDamage(4);
        target.SetDoT(2, 2);
    }
}


void Abilities::IcicleSpear(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(3);
        target.SetDoT(3, 3);
    }
}


void Abilities::PoisonShot(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(80);

    if (rng.GetDidHit())
    {
        target.TakeDamage(3);
        target.SetDoT(2, 5);
    }
}


// ============================================================
// RESOURCE TRADEOFF ABILITIES
// ============================================================

void Abilities::BloodPierce(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(100);

    if (rng.GetDidHit())
    {
        target.TakeDamage(6);
        caster.TakeDamage(5);
    }
}


void Abilities::BloodBomb(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(10);
        caster.TakeDamage(10);
    }
}


// ============================================================
// ABILITY RANGE GETTERS
// ============================================================

int Abilities::GetMinRange(int ability)
{
    if (ability < 0 || ability >= 10)
    {
        return 1;
    }

    return minRange[ability];
}


int Abilities::GetMaxRange(int ability)
{
    if (ability < 0 || ability >= 10)
    {
        return 1;
    }

    return maxRange[ability];
}