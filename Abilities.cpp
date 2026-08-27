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

void Abilities::WaterBolt(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(3);

        int newHP = caster.getHealth() + 5;
        if (newHP > caster.getMaxHealth())
        {
            newHP = caster.getMaxHealth();
        }
        caster.setHealth(newHP);
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

void Abilities::BloomingFlowers(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(85);

    if (rng.GetDidHit())
    {
        int extraDMG = rand() % 8;

        target.TakeDamage(3 + extraDMG);

        int newHP = caster.getHealth() + 4;
        if (newHP > caster.getMaxHealth())
        {
            newHP = caster.getMaxHealth();
        }
        caster.setHealth(newHP);
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

void Abilities::BloodPierce(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(100);

    if (rng.GetDidHit())
    {
        target.TakeDamage(6);
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

// NEW ABILITY TESTING
// TESTING CODE
Abilities::Abilities()
{
    // Array of ability names
    RandoAbilityList[1] = "Fire Ball";
    RandoAbilityList[2] = "Boulder Throw";
    RandoAbilityList[3] = "Blood Pierce";
    RandoAbilityList[4] = "Poison Shot";
    RandoAbilityList[5] = "Lightning Bolt";
    RandoAbilityList[6] = "Blood Bomb";
    RandoAbilityList[7] = "Water Bolt";
    RandoAbilityList[8] = "Air Cutter";
    RandoAbilityList[9] = "Blooming Flowers";

    // Array of ability bools
    RandoAbilityBools[1] = false;
    RandoAbilityBools[2] = false;
    RandoAbilityBools[3] = false;
    RandoAbilityBools[4] = false;
    RandoAbilityBools[5] = false;
    RandoAbilityBools[6] = false;
    RandoAbilityBools[7] = false;
    RandoAbilityBools[8] = false;
    RandoAbilityBools[9] = false;

    // Array of Class Specific spells
    ClassAbilityList[1] = "Hero's Light";
    ClassAbilityList[2] = "Sworvant";
    ClassAbilityList[3] = "Sworvant:Sactifice";
    ClassAbilityList[4] = "Magic Missile";
    ClassAbilityList[5] = "Catclysm";
    ClassAbilityList[6] = "Icicle Spear";
    ClassAbilityList[7] = "Magic Arrow";
    ClassAbilityList[8] = "Bullseye";
    ClassAbilityList[9] = "Phoenix Arrow";

    // Array of Class Specific bools
    ClassAbilityBools[1] = false;
    ClassAbilityBools[2] = false;
    ClassAbilityBools[3] = false;
    ClassAbilityBools[4] = false;
    ClassAbilityBools[5] = false;
    ClassAbilityBools[6] = false;
    ClassAbilityBools[7] = false;
    ClassAbilityBools[8] = false;
    ClassAbilityBools[9] = false;
}

//TESTING CLASS ABILITY RANGE GETTERS
int Abilities::GetMinClsAbiRange(int clsability)
{
    if (clsability < 0 || clsability >= 10)
    {
        return 1;
    }

    return ClassAbilityMinRange[clsability];
}


int Abilities::GetMaxClsAbiRange(int clsability)
{
    if (clsability < 0 || clsability >= 10)
    {
        return 1;
    }

    return ClassAbilityMaxRange[clsability];
}

//CLASS SPECIFIC ABILITIES HERE
//TESTING CODE

//WARRIOR STARTS HERE//
void Abilities::HerosLight(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(95);

    if (rng.GetDidHit())
    {
        target.TakeDamage(6);

        int newHP = caster.getHealth() + 8;
        if (newHP > caster.getMaxHealth())
        {
            newHP = caster.getMaxHealth();
        }
        caster.setHealth(newHP);
    }
}

void Abilities::Sworvant(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(100);

    if (rng.GetDidHit())
    {
        target.TakeDamage(10);
        target.SetDoT(4, 3);
    }
}

void Abilities::SworvantSacrifice(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(16);
        target.SetDoT(2, 2);

        caster.TakeDamage(15);
    }
}

//MAGE STARTS HERE//
void Abilities::MagicMissile(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(85);

    if (rng.GetDidHit())
    {
        target.TakeDamage(10);
    }
}

void Abilities::Cataclysm(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        int extraDMG = rand() % 16;

        target.TakeDamage(15 + extraDMG);
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

//ARCHER STARTS HERE//

void Abilities::MagicArrow(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(100);

    if (rng.GetDidHit())
    {
        target.TakeDamage(4);
    }
}

void Abilities::Bullseye(Entity& target)
{
    RNG rng;
    rng.AbilityHitOrMiss(95);

    if (rng.GetDidHit())
    {
        int extraDMG = rand() % 11;

        target.TakeDamage(10 + extraDMG);
    }
}

void Abilities::PhoenixArrow(Entity& target, Entity& caster)
{
    RNG rng;
    rng.AbilityHitOrMiss(90);

    if (rng.GetDidHit())
    {
        target.TakeDamage(6);
        target.SetDoT(3, 5);

        caster.TakeDamage(9);
    }
}

int Abilities::GetStaminaCost(int ability)
{
    if (ability < 1 || ability > 9) return 0;
    return staminaCost[ability];
}

int Abilities::GetClassStaminaCost(int ability)
{
    if (ability < 1 || ability > 9) return 0;
    return classStaminaCost[ability];
}