#pragma once

class RNG
{
private:
    int GotHit;
    int Accuracy;
    bool DidHit;
    bool Dodged;

public:
    RNG();

    void SetAccuracy(int accuracy); // Accuracy
    void HitOrMiss();
    void AbilityHitOrMiss(int chance);
    void Dodge(int chance); // Dodge

    bool CriticalHit(int chance); // Critical Hit
    bool GetDidHit();
    bool GetDodged();
};
