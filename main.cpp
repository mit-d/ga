#include <algorithm>
#include <iostream>
#include "Chrom.h"
#include "Population.h"

using namespace std;
using namespace ga;

int main() {
    vector<Chrom> population(100, Chrom(10, -5, 5));

    for (auto& i : population) i.randomize();
    std::vector<Chrom> sel(50);

    for (int i = 0; i < 1000; ++i) {
        std::stable_sort(population.begin(), population.end());

        // Select + Replace
        std::copy(population.begin(), population.begin() + 50,
                  population.rbegin());
        std::shuffle(population.begin() + 2, population.end(), ga::rng);

        // Cross
        cross(population.begin() + 2, population.end());

        // Mutate
        for (auto it = population.begin() + 1; it != population.end(); ++it)
            (*it).mutate();

        // Print
        static double last_fit = 0.0;
        if (population.front().fitness() != last_fit) {
            cout << population.front().fitness() << " | " << population.front()
                 << endl;
            last_fit = population.front().fitness();
        }
    }
}
