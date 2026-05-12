#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include "train.h"

int runExperiment(int n, const std::vector<bool>& lights) {
    Train train;
    for (int i = 0; i < n; i++) {
        train.addCar(lights[i]);
    }
    int length = train.getLength();
    return train.getOpCount();
}

int main() {
    std::vector<int> sizes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 250, 300, 350, 400, 450, 500};
    
    std::ofstream file("result/data.csv");
    file << "n,all_off,all_on,random\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    for (int n : sizes) {
        std::cout << "Testing n = " << n << std::endl;
        
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
    
    std::ofstream script("plot.py");
    script << "import pandas as pd\n"
           << "import matplotlib.pyplot as plt\n"
           << "import numpy as np\n"
           << "from scipy import stats\n\n"
           << "df = pd.read_csv('result/data.csv')\n\n"
           << "plt.figure(figsize=(12, 8))\n\n"
           << "x = df['n'].values\n"
           << "y_off = df['all_off'].values\n"
           << "y_on = df['all_on'].values\n"
           << "y_rand = df['all_random'].values\n\n"
           << "plt.scatter(x, y_off, label='All off', alpha=0.6)\n"
           << "plt.scatter(x, y_on, label='All on', alpha=0.6)\n"
           << "plt.scatter(x, y_rand, label='Random', alpha=0.6)\n\n"
           << "z_off = np.polyfit(x, y_off, 2)\n"
           << "p_off = np.poly1d(z_off)\n"
           << "plt.plot(x, p_off(x), '--', label=f'Trend all off: {z_off[0]:.2f}n² + {z_off[1]:.2f}n + {z_off[2]:.2f}')\n\n"
           << "z_on = np.polyfit(x, y_on, 2)\n"
           << "p_on = np.poly1d(z_on)\n"
           << "plt.plot(x, p_on(x), '--', label=f'Trend all on: {z_on[0]:.2f}n² + {z_on[1]:.2f}n + {z_on[2]:.2f}')\n\n"
           << "z_rand = np.polyfit(x, y_rand, 2)\n"
           << "p_rand = np.poly1d(z_rand)\n"
           << "plt.plot(x, p_rand(x), '--', label=f'Trend random: {z_rand[0]:.2f}n² + {z_rand[1]:.2f}n + {z_rand[2]:.2f}')\n\n"
           << "plt.xlabel('Train length (n)')\n"
           << "plt.ylabel('Number of operations')\n"
           << "plt.title('Time Complexity: Operations vs Train Length')\n"
           << "plt.legend()\n"
           << "plt.grid(True, alpha=0.3)\n"
           << "plt.savefig('result/plot.png', dpi=150, bbox_inches='tight')\n"
           << "plt.show()\n";
    script.close();
    
    std::cout << "\nExperiment complete. Run: python3 plot.py\n";
    
    return 0;
}
