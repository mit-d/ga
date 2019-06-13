#include <algorithm>
#include <cfloat>
#include <iostream>
#include "Chrom.h"
#include "ga.h"

using namespace std;
using namespace ga;

int main() {
  // Initialize Population
  vector<Chrom> population(100, Chrom(10));
  for (auto& i : population) i.range(-5, 5).randomize();
  sort(population.begin(), population.end());

  // Main evolution for loop
  for (int i = 0; i < 10000; ++i) {
    // Select Parents
    static decltype(population) sel(population.size() / 2);
    copy(population.begin(), population.begin() + population.size() / 2,
         population.rbegin());

    // Cross (Parents -> Now Children)
    shuffle(population.begin() + 2, population.end(), ga::rng);
    cross(population.begin() + 2, population.end());

    // Mutate Children
    for (auto it = population.begin() + 1; it != population.end(); ++it)
      (*it).mutate();

    // Keep Population Sorted
    sort(population.begin(), population.end());

    // Print if new best fitness
    static double last_fit = 0.0;
    if (population.front().fitness() != last_fit) {
      cout << population.front().fitness() << " | " << population.front()
           << endl;
      last_fit = population.front().fitness();
    }
  }  // for
}
