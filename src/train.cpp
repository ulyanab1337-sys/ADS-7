// Copyright 2026 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car *current = first;
    do {
        Car *next = current->next;
        delete current;
        current = next;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car *newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car *last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    if (!first) return 0;

    countOp = 0;
    Car *current = first;

    current->light = false;
    int counter = 0;
    int steps = 0;

    while (true) {
        current = current->next;
        countOp++;
        steps++;

        if (current->light) {
            current->light = false;
            steps = 0;
            counter = 0;
        } else {
            if (steps > 0) {
                counter++;
                if (counter == steps) {
                    const Car *temp = current;
                    bool allOff = true;
                    for (int i = 0; i < steps; i++) {
                        temp = temp->prev;
                        countOp++;
                        if (temp->light) {
                            allOff = false;
                            break;
                        }
                    }
                    if (allOff) {
                        return steps;
                    }
                    counter = 0;
                }
            }
        }
    }
}
