#pragma once

class RNG
{
private:
    int GotHit;
    int Accuracy;

    bool DidHit;
    bool Dodged;
    bool Thorned;

public:
    RNG();

    void SetAccuracy(int accuracy);
    void HitOrMiss();
    void AbilityHitOrMiss(int chance);
    void Dodge(int chance);
    void Thorns(int chance);

    bool CriticalHit(int chance);

    bool GetDidHit();
    bool GetDodged();
    bool GetThorns();
};
