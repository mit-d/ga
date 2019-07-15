#include <algorithm>
#include <cfloat>
#include <iostream>

/* #include "Niche.h" */
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
  auto population = vector(256, Rastragin(4));
  for (auto& i : population) i.randomize();
  std::sort(population.begin(), population.end());

  // MAIN LOOP //
  for (int i = 0; i < 1000; ++i) {
    // Select Parents *** top 50%
    copy(population.begin(), population.begin() + population.size() / 2,
         population.rbegin());

    // Cross (Parents -> Now Children) ***
    shuffle(population.begin() + 2, population.end(), ga::rng);
    cross(population.begin() + 2, population.end());

    // Mutate Children ***
    for (auto it = population.begin() + 1; it != population.end(); ++it)
      (*it).mutate();

    // Keep Population Sorted
    std::sort(population.begin(), population.end());

    // Print if new best fitness
    static double last_fit = 0.0;
    std::nth_element(population.begin(), population.begin(), population.end());

  }  // for
  cout << setprecision(50) << population.front().fitness() << endl;
}
