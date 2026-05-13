// Copyright 2026 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car *current = first;
    Car *nextCar;
    do {
        nextCar = current->next;
        delete current;
        current = nextCar;
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
    int length = 0;
    bool found = false;
    
    while (!found) {
        length++;
        for (int i = 0; i < length; i++) {
            current = current->next;
            countOp++;
        }
        
        if (!current->light) {
            current->light = true;
            Car *temp = current;
            bool allOff = true;
            for (int i = 0; i < length; i++) {
                temp = temp->prev;
                countOp++;
                if (temp->light) {
                    allOff = false;
                    break;
                }
            }
            if (allOff) {
                found = true;
            }
        } else {
            current->light = false;
            length = 0;
        }
    }
    
    return length;
}
