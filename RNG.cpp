#include "RNG.h"
#include <iostream>

using namespace std;
RNG::RNG() {
    GotHit = 0;
    Accuracy = 0;
    DidHit = false;
}
void RNG::SetAccuracy (int accuracy) {
    Accuracy = accuracy;
}

void RNG::HitOrMiss() {
    GotHit = rand() % 101 + Accuracy;
    if (GotHit >= 31) {
        cout << "You have Hit the enemy (" << GotHit << "%)" << endl;
        DidHit = true;
    }
    else {
        cout << "You have missed (" << GotHit << "%)" << endl;
        DidHit = false;
    }
}

bool RNG::GetDidHit() {
    return DidHit;
}