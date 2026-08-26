#pragma once
#include <string>
#include <iostream>
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
    //10 = Bulleyes
    //11 = Magic Arrow

    int minRange[12] = {
        1, // NULL IGNORE INDEX 0
        1, // FIREBALL
        1, // BOULDER
        1, // PIERCE
        1, // POISON
        1, // LIGHTNING
        1, // BOMB
        1, // WATER
        1, // AIR
        1, // FLOWER
        1  //
    };

    int maxRange[12] = {
        1, // NULL IGNORE INDEX 0
        3, // FIREBALL
        2, // BOULDER
        4, // PIERCE
        3, // POISON
        5, // LIGHTNING
        3, // BOMB
        3, // WATER
        5, // AIR
        5, // FLOWER
        1  //

    };

    //NEW CODE DONT TOUCH, TESTING
    int ClassAbilityMinRange[11] =
    {
        1, //NULL IGNORE INDEX 0
        1, //HEROS LIGHT
        1, //SWORVANT
        1, //SWORVANT SACRIFICE
        1, //MAGIC MISSILE
        1, //CATCLYSM
        1, //ICICLE SPEAR
        1, //MAGIC ARROW
        1, //BULLSEYE
        1, //PHOENIX ARROW
        1
    };

    int ClassAbilityMaxRange[11] =
    {
        1, //NULL IGNORE INDEX 0
        2, //HEROS LIGHT
        3, //SWORVANT
        3, //SWORVANT SACRIFICE
        4, //MAGIC MISSILE
        4, //CATCLYSM
        2, //ICICLE SPEAR
        3, //MAGIC ARROW
        5, //BULLSEYE
        7, //PHOENIX ARROW
        1
    };

public:
    // Ability IDs
    /*enum AbilityID
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
        WATER_BOLT = 9,
        BULLSEYE = 10,
        MAGIC_ARROW = 11
    };*/

    //TESTING CODE
    //TESTING NEW CODE
    std::string RandoAbilityList[10]; //ability list of names to get randomised set printed for player to see, index 0 is unused so array x of abilities + 1
    std::string ClassAbilityList[10]; //class specific ability list of names
    bool RandoAbilityBools[10]; //ability bools to check if player can or has the spell avaliable
    bool ClassAbilityBools[10]; //class ability bools to check if player has or can use the spell
    Abilities();

    //TRYING OUT NEW LIST DONT TOUCH YET
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
        //Warrior
        HEROS_LIGHT = 1,
        SWORVANT = 2,
        SWORVANT_SACRIFICE = 3,
        //Mage
        MAGIC_MISSILE = 4,
        CATCLYSM = 5,
        ICICLE_SPEAR = 6,
        //Archer
        MAGIC_ARROW = 7,
        BULLSEYE = 8,
        PHOENIX_ARROW = 9
    };

    //ability choice nums
    int randoability1, randoability2, randoability3, randoability4, randoability5, randoability6;
    //ability answers
    int abilityans1, abilityans2;
    

    // Direct Damage
    void LightningBolt(Entity& target);
    void WaterBolt(Entity& target, Entity& caster);
    void BoulderThrow(Entity& target);
    void Aircutter(Entity& target);
    void BloomingFlowers(Entity& target, Entity& caster);

    // Damage Over Time
    void Fireball(Entity& target);
    void PoisonShot(Entity& target);

    // Resource Tradeoff
    void BloodPierce(Entity& target);
    void BloodBomb(Entity& target, Entity& caster);


    //NEW ADDITION//
    //Class Specific Spells
    //Archer
    void MagicArrow(Entity& target); //Direct DMG
    void Bullseye(Entity& target); //Direct DMG
    void PhoenixArrow(Entity& target, Entity& caster); //Resource Tradeoff

    //Warrior
    void HerosLight(Entity& target, Entity& caster); //Direct DMG
    void Sworvant(Entity& target); //DoT
    void SworvantSacrifice(Entity& target, Entity& caster); //Resource Tradeoff

    //Mage
    void MagicMissile(Entity& target); //Direct DMG
    void Cataclysm(Entity& traget); //Direct DMG
    void IcicleSpear(Entity& target); //DoT

    //NEW TESTING RANGE GETTERS FOR CLASS ABILITIES
    // Range getters
    int GetMinClsAbiRange(int clsability);
    int GetMaxClsAbiRange(int clsability);


    // Range getters for normal abilities
    int GetMinRange(int ability);
    int GetMaxRange(int ability);
};