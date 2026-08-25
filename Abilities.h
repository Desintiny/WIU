#pragma once
#include "Entity.h"

class Abilities
{
private:
    // Ability range data
    // Index:
    // 0 = Fireball
    // 1 = Magic Missile
    // 2 = Blood Pierce
    // 3 = Icicle Spear
    // 4 = Lightning Bolt
    // 5 = Blood Bomb
    // 6 = Poison Shot
    // 7 = Air Cutter
    // 8 = Boulder Throw
    // 9 = Water Bolt

    int minRange[10] = {
        1, // Fireball
        1, // Magic Missile
        1, // Blood Pierce
        1, // Icicle Spear
        1, // Lightning Bolt
        1, // Blood Bomb
        1, // Poison Shot
        1, // Air Cutter
        1, // Boulder Throw
        1  // Water Bolt
    };

    int maxRange[10] = {
        3, // Fireball
        4, // Magic Missile
        4, // Blood Pierce
        2, // Icicle Spear
        5, // Lightning Bolt
        3, // Blood Bomb
        3, // Poison Shot
        5, // Air Cutter
        2, // Boulder Throw
        3  // Water Bolt
    };

    int staminaCost[10] =
    {
        3, // Fireball
        3, // Magic Missile
        2, // Blood Pierce
        3, // Icicle Spear
        4, // Lightning Bolt
        4, // Blood Bomb
        3, // Poison Shot
        2, // Air Cutter
        2, // Boulder Throw
        2  // Water Bolt
    };

public:
    // Ability IDs
    enum AbilityID
    {
        FIREBALL = 0,
        MAGIC_MISSILE = 1,
        BLOOD_PIERCE = 2,
        ICICLE_SPEAR = 3,
        LIGHTNING_BOLT = 4,
        BLOOD_BOMB = 5,
        POISON_SHOT = 6,
        AIR_CUTTER = 7,
        BOULDER_THROW = 8,
        WATER_BOLT = 9
    };

    // Direct Damage
    void LightningBolt(Entity& target);
    void MagicMissile(Entity& target);
    void WaterBolt(Entity& target, Entity& caster);
    void BoulderThrow(Entity& target);
    void Aircutter(Entity& target);

    // Damage Over Time
    void Fireball(Entity& target);
    void IcicleSpear(Entity& target);
    void PoisonShot(Entity& target);

    // Resource Tradeoff
    void BloodPierce(Entity& target, Entity& caster);
    void BloodBomb(Entity& target, Entity& caster);

    // Range getters
    int GetMinRange(int ability);
    int GetMaxRange(int ability);
    int GetStaminaCost(int ability);
};