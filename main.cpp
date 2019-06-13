#include <algorithm>
#include <cfloat>
#include <iostream>

#include "ga.h"

#include "Ackley.h"
#include "Rastragin.h"
#include "Rosenbrock.h"
#include "Schwefel.h"
#include "Spherical.h"

using namespace std;
using namespace ga;

int main() {
  // INITIALIZE POPULATION //
  auto population = vector(100, Rosenbrock(10));
  for (auto& i : population) i.randomize();
  std::sort(population.begin(), population.end());

  // MAIN LOOP //
  for (int i = 0; i < 10000; ++i) {
    // Select Parents ***
    copy(population.begin(), population.begin() + population.size() / 2,
         population.rbegin());

    // Cross (Parents -> Now Children) ***
    shuffle(population.begin() + 2, population.end(), ga::rng);
    cross(population.begin() + 2, population.end());

    // Mutate Children ***
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
