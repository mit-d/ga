#include <algorithm>
#include <iostream>
#include "Chrom.h"
#include "Population.h"

using namespace std;
using namespace ga;

int main() {
  vector<Chrom> population(100, Chrom(10));

  for (auto& i : population) i.range(-5, 5).randomize();
  decltype(population) sel(50);

  for (int i = 0; i < 1000; ++i) {
    std::stable_sort(population.begin(), population.end());

    // Select + Replace
    std::copy(population.begin(), population.begin() + population.size() / 2,
              population.rbegin());
    std::shuffle(population.begin() + 2, population.end(), ga::rng);

    // Cross
    cross(population.begin() + 2, population.end());

    // Mutate
    for (auto it = population.begin() + 1; it != population.end(); ++it)
      (*it).mutate();

    // Print
    static double last_fit = 0.0;
    if (population.front().fitness() !=
        last_fit) {  // Front will only change if a better fitness is found due
                     // to elitism
      cout << population.front().fitness() << " | " << population.front()
           << endl;
      last_fit = population.front().fitness();
    }
  }
}
