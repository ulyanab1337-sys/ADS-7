// Copyright 2026 NNTU-CS

#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) {
        return;
    }

    Car* current = first;
    Car* nextCar;

    do {
        nextCar = current->next;
        delete current;
        current = nextCar;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};

    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;

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
    if (!first) {
        return 0;
    }

    countOp = 0;

    int length = 1;

    const Car* current = first->next;
    countOp++;

    while (current != first) {
        current = current->next;
        countOp++;
        length++;
    }

    return length;
}
