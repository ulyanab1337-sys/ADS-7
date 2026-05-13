// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "train.h"

int main() {
    std::srand(time(nullptr));

    std::cout << "n\tall_off\t\tall_on\t\trandom\n";

    for (int n = 2; n <= 100; n++) {
        int movesOff, movesOn, movesRand;

        {
            Train train;
            for (int i = 0; i < n; i++)
                train.appendWagon(false);
            train.calcLength();
            movesOff = train.getTotalMoves();
        }

        {
            Train train;
            for (int i = 0; i < n; i++)
                train.appendWagon(true);
            train.calcLength();
            movesOn = train.getTotalMoves();
        }

        {
            Train train;
            for (int i = 0; i < n; i++)
                train.appendWagon(std::rand() % 2);
            train.calcLength();
            movesRand = train.getTotalMoves();
        }

        std::cout << n << "\t" << movesOff << "\t\t" << movesOn << "\t\t"
                  << movesRand << "\n";
    }

    return 0;
}
