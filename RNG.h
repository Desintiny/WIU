#pragma once

class RNG
{
private:
    int GotHit;
    int Accuracy;
    bool DidHit;

public:
    RNG();

    void SetAccuracy(int accuracy); // Accuracy
    void HitOrMiss();
    void AbilityHitOrMiss(int chance);

    bool CriticalHit(int chance);    // Critical Hit
    bool GetDidHit();
};
