// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

int Train::getOpCount() {
    return countOp;
}

void Train::addCar(bool light) {
    Car *newCar = new Car;
    newCar->light = light;

    if (first == nullptr) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
        return;
    }

    Car *last = first->prev;
    newCar->next = first;
    newCar->prev = last;
    last->next = newCar;
    first->prev = newCar;
}

int Train::getLength() {
    Car *current = first;
    current->light = true;

    while (true) {
        int steps = 0;

        do {
            current = current->next;
            countOp++;
            steps++;
        } while (!current->light);

        current->light = false;

        for (int i = 0; i < steps; i++) {
            current = current->prev;
            countOp++;
        }

        if (!current->light) {
            return steps;
        }
    }
}
