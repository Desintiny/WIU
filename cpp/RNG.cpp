#include "RNG.h"
#include <iostream>
#include <cstdlib>

using namespace std;

RNG::RNG()
{
    GotHit = 0;
    Accuracy = 0;
    DidHit = false;
    Dodged = false;
}

void RNG::SetAccuracy(int accuracy)
{
    Accuracy = accuracy;
}

void RNG::HitOrMiss()
{
    // Basic attack: equipment accuracy applies
    GotHit = rand() % 100 + Accuracy;

    if (GotHit >= 100)
    {
        cout << "You have Hit the enemy (100%)\n\n";
        DidHit = true;
    }
    else if (GotHit >= 31)
    {
        cout << "You have Hit the enemy (" << GotHit << "%)\n\n";
        DidHit = true;
    }
    else
    {
        cout << "You have missed (" << GotHit << "%)\n\n";
        DidHit = false;
    }
}

void RNG::AbilityHitOrMiss(int chance)
{
    // Ability: equipment accuracy does NOT apply
    int roll = rand() % 100;

    if (roll < chance)
    {
        cout << "Your Ability Hits. (" << chance << "%)\n\n";
        DidHit = true;
    }
    else
    {
        cout << "Your Ability missed. (" << chance << "%)\n\n";
        DidHit = false;
    }
}

void RNG::Dodge(int chance)
{
    int roll = rand() % 100;

    if (roll < chance)
    {
        Dodged = true;
        cout << "You dodged the attack! (" << chance << "%)\n\n";
    }
    else
    {
        Dodged = false;
    }
}

bool RNG::GetDodged()
{
    return Dodged;
}

bool RNG::GetDidHit()
{
    return DidHit;
}

bool RNG::CriticalHit(int chance)
{
    int roll = rand() % 100;

    if (roll < chance)
    {
        return true;
    }

    return false;
}
