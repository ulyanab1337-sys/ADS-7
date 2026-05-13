// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : entryPoint(nullptr), totalMoves(0) {}

int Train::getTotalMoves() {
    return totalMoves;
}

void Train::appendWagon(bool bulbState) {
    Wagon *newWagon = new Wagon;
    newWagon->bulb = bulbState;

    if (entryPoint == nullptr) {
        entryPoint = newWagon;
        newWagon->nextWagon = newWagon;
        newWagon->prevWagon = newWagon;
        return;
    }

    Wagon *lastWagon = entryPoint->prevWagon;
    newWagon->nextWagon = entryPoint;
    newWagon->prevWagon = lastWagon;

    lastWagon->nextWagon = newWagon;
    entryPoint->prevWagon = newWagon;
}

int Train::calcLength() {
    Wagon *current = entryPoint;
    current->bulb = true;

    while (true) {
        int stepCount = 0;

        do {
            current = current->nextWagon;
            totalMoves++;
            stepCount++;
        } while (!current->bulb);

        current->bulb = false;

        for (int i = 0; i < stepCount; i++) {
            current = current->prevWagon;
            totalMoves++;
        }

        if (!current->bulb) {
            return stepCount;
        }
    }
}
