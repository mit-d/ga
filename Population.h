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
template <typename I>  // forward iterator
I cross(I first, I last) {
  auto second = first + 1;
  while (first != last && second != last) {
    (*first).cross(*second);
    first += 2;
    second += 2;
  }
  return first;
}

template <typename I> /* random access iterator */
void select_fill(I from_first, I from_last, I dest_first, I dest_last) {
  std::partial_sort_copy(from_first, from_last, dest_first, dest_last);
  std::shuffle(dest_first, dest_last, ga::rng);
};
}  // namespace ga
#endif
