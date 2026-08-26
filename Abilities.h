#pragma once
#include <string>
#include <iostream>
#include "Entity.h"

class Abilities
{
private:
    // Index 0 is unused so menu numbers and ability IDs match directly.
    int minRange[10] = {
        1,
        1, // Fireball
        1, // Boulder Throw
        1, // Blood Pierce
        1, // Poison Shot
        1, // Lightning Bolt
        1, // Blood Bomb
        1, // Water Bolt
        1, // Air Cutter
        1  // Blooming Flowers
    };

    int maxRange[10] = {
        1, //INDEX 0 IGNORE
        3, // Fireball
        2, // Boulder Throw
        4, // Blood Pierce
        3, // Poison Shot
        5, // Lightning Bolt
        3, // Blood Bomb
        3, // Water Bolt
        5, // Air Cutter
        5  // Blooming Flowers
    };

    //NORMAL COST HERE
    int staminaCost[10] = {
        0, //INDEX 0 IGNORE
        5, // Fireball
        7, // Boulder Throw
        0, // Blood Pierce
        4, // Poison Shot
        3, // Lightning Bolt
        0, // Blood Bomb
        4, // Water Bolt
        6, // Air Cutter
        8  // Blooming Flowers
    };

    int ClassAbilityMinRange[10] = {
        1,
        1, // Hero's Light
        1, // Sworvant
        1, // Sworvant Sacrifice
        1, // Magic Missile
        1, // Cataclysm
        1, // Icicle Spear
        1, // Magic Arrow
        1, // Bullseye
        1  // Phoenix Arrow
    };

    int ClassAbilityMaxRange[10] = {
        1,
        2, // Hero's Light
        3, // Sworvant
        3, // Sworvant Sacrifice
        4, // Magic Missile
        4, // Cataclysm
        2, // Icicle Spear
        3, // Magic Arrow
        5, // Bullseye
        7  // Phoenix Arrow
    };

    //COST HERE
    int classStaminaCost[10] = {
        0,
        10, // Hero's Light
        15, // Sworvant
        0, // Sworvant Sacrifice
        8, // Magic Missile
        15, // Cataclysm
        3, // Icicle Spear
        3, // Magic Arrow
        5, // Bullseye
        0  // Phoenix Arrow
    };

public:
    std::string RandoAbilityList[10];
    std::string ClassAbilityList[10];
    bool RandoAbilityBools[10];
    bool ClassAbilityBools[10];

    Abilities();

    enum AbilityID
    {
        FIREBALL = 1,
        BOULDER_THROW = 2,
        BLOOD_PIERCE = 3,
        POISON_SHOT = 4,
        LIGHTNING_BOLT = 5,
        BLOOD_BOMB = 6,
        WATER_BOLT = 7,
        AIR_CUTTER = 8,
        BLOOMING_FLOWER = 9
    };

    enum ClassAbilityID
    {
        HEROS_LIGHT = 1,
        SWORVANT = 2,
        SWORVANT_SACRIFICE = 3,
        MAGIC_MISSILE = 4,
        CATCLYSM = 5,
        ICICLE_SPEAR = 6,
        MAGIC_ARROW = 7,
        BULLSEYE = 8,
        PHOENIX_ARROW = 9
    };

    int randoability1, randoability2, randoability3, randoability4, randoability5, randoability6;
    int abilityans1, abilityans2;

    void LightningBolt(Entity& target);
    void WaterBolt(Entity& target, Entity& caster);
    void BoulderThrow(Entity& target);
    void Aircutter(Entity& target);
    void BloomingFlowers(Entity& target, Entity& caster);

    void Fireball(Entity& target);
    void PoisonShot(Entity& target);

    void BloodPierce(Entity& target);
    void BloodBomb(Entity& target, Entity& caster);

    void MagicArrow(Entity& target);
    void Bullseye(Entity& target);
    void PhoenixArrow(Entity& target, Entity& caster);

    void HerosLight(Entity& target, Entity& caster);
    void Sworvant(Entity& target);
    void SworvantSacrifice(Entity& target, Entity& caster);

    void MagicMissile(Entity& target);
    void Cataclysm(Entity& target);
    void IcicleSpear(Entity& target);

    int GetMinClsAbiRange(int clsability);
    int GetMaxClsAbiRange(int clsability);
    int GetClassStaminaCost(int clsability);

    int GetMinRange(int ability);
    int GetMaxRange(int ability);
    int GetStaminaCost(int ability);
};
