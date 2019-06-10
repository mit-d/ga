#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <vector>
#include "Chrom.h"

namespace ga {
class Population {
 public:
  Population(int t_chromosomes, int t_dimensions)
      : n_dimensions(t_dimensions), n_chromosomes(t_chromosomes){};
  Population(int t_chromosomes) : Population(t_chromosomes, 30){};
  virtual ~Population(){};

 private:
  size_t n_dimensions{0};
  size_t n_chromosomes{0};
  std::vector<ga::Chrom> m_data;

 public:
  void evolve(const size_t n) {
    for (size_t i = 0; i < n; ++i) {
      select();
      mutate();
      cross(1);
    }
  };
  virtual void select() { std::stable_sort(m_data.begin(), m_data.end()); };
  virtual void mutate() {
    for (auto& i : m_data) i.mutate();
  };
  virtual void cross(int t_elite) {
    for (auto it = m_data.begin() + t_elite; it < m_data.end(); it += 2)
      if (it + 1 != m_data.end()) {
        (*it).cross(*(it + 1));
      }
  };
  std::tuple<size_t, size_t> size() {
    return std::make_tuple(n_dimensions, n_chromosomes);
  };
};

/* Cross a vector of genomes */
template <typename ForwardIterator>
ForwardIterator cross(ForwardIterator first, ForwardIterator last) {
  auto second = first + 1;
  while (first != last && second != last) {
    (*first).cross(*second);
    first += 2;
    second += 2;
  }
  return first;
}

/* Copy the best individuals from (pool) to (dest) */
template <typename RandomAccessIterator>
void select_fill(RandomAccessIterator pool_first,
                 RandomAccessIterator pool_last,
                 RandomAccessIterator dest_first,
                 RandomAccessIterator dest_last) {
  std::partial_sort_copy(pool_first, pool_last, dest_first, dest_last);
  std::shuffle(dest_first, dest_last, ga::rng);
};

// Select in Place
template <typename RandomAccessIterator, typename ForwardIterator>
void select_tourn(RandomAccessIterator first, RandomAccessIterator last,
                  ForwardIterator dfirst) {
  std::sample(first, last, dfirst, static_cast<size_t>(last - first), rng);
};
}  // namespace ga
#endif
