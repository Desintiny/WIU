#pragma once

class RNG
{
private:
    int GotHit;
    int Accuracy;
    bool DidHit;

public:
    RNG();

    void SetAccuracy(int accuracy);

    void HitOrMiss();                  // Basic attack
    void AbilityHitOrMiss(int chance); // Ability

    bool GetDidHit();
};
