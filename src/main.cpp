// src/main.cpp
// Copyright 2026 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "train.h"

int runExperiment(int n, const std::vector<bool>& lights) {
    Train train;
    for (int i = 0; i < n; i++) {
        train.addCar(lights[i]);
    }
    train.getLength();
    return train.getOpCount();
}

int main() {
    std::vector<int> sizes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
                               120, 140, 160, 180, 200, 250, 300, 350,
                               400, 450, 500};

    std::ofstream file("result/data.csv");
    file << "n,all_off,all_on,random\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int n : sizes) {
        std::vector<bool> allOff(n, false);
        std::vector<bool> allOn(n, true);
        std::vector<bool> random(n);
        for (int i = 0; i < n; i++) {
            random[i] = dis(gen);
        }

        int opsOff = runExperiment(n, allOff);
        int opsOn = runExperiment(n, allOn);
        int opsRandom = runExperiment(n, random);

        file << n << "," << opsOff << "," << opsOn << "," << opsRandom << "\n";
    }

    file.close();
    return 0;
}
