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

    Car* start = first;
    start->light = true;

    int len = 1;

    while (true) {
        Car* current = start;

        for (int i = 0; i < len; i++) {
            current = current->next;
            countOp++;
        }

        if (current->light) {
            current->light = false;

            Car* check = current;

            for (int i = 0; i < len; i++) {
                check = check->prev;
                countOp++;
            }

            if (check == start) {
                return len;
            }

            len = 1;
        } else {
            current->light = true;
            len++;
        }
    }
}
