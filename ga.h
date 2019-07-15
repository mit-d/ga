#ifndef _ga_h_
#define _ga_h_

#include <vector>
#include "Chrom.h"

namespace ga {

struct parameters {
  const bool free_lunch = false;
  size_t n_chrom = 512;
  size_t n_genes = 32;
  size_t max_generations = 2000;
  double crossover_pct = 0.80;
  double pct_error = 0.001;
  size_t n_elite = 2;
  size_t n_islands = 4;
  double fit_sharing_amount = 0.2;
};

/* Cross a vector of genomes */
template <typename InputIterator>
InputIterator cross(InputIterator first, InputIterator last) {
  auto second = first + 1;
  while (first != last && second != last) {
    (*first).cross(*second);
    first += 2;
    second += 2;
  }
  return first;
}

template <typename InputIterator>
InputIterator cross(InputIterator first, InputIterator last,
                    const size_t& n_island) {
  // Cross within each island
  auto isl_sz = static_cast<size_t>(last - first);
}

template <typename InputIterator, class T>
double getSharedFitness(InputIterator first, InputIterator last, const T index,
                        const double& share_amount) {
  double denominator = 0.0;
  double min_dist = 100;
  while (first != last) {
    auto dist = first->dist2(index);
    if (dist < min_dist) denominator += 1 - dist / share_amount;
    ++first;
  }

  return index.fitness() / denominator;
}

template <typename InputIterator, class Chromosome>
Chromosome select(InputIterator first, InputIterator last) {
  // Set amount of sharing here. A value of 1 will reduce an exact copy to
  // zero
  static const double Amount = .1;
}

}  // namespace ga
#endif  // _ga_h_
