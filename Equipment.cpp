#include "Equipment.h"

Equipment::Equipment() {
    Accuracy = 0;
}

int Equipment::GetAccuracy() {
    return Accuracy;
}

void Equipment::SetAccuracy(int accuracy) {
    Accuracy = accuracy;
}