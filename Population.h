#ifndef _POPULATION_H_
#define _POPULATION_H_

#include <vector>
#include "Chrom.h"

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
  virtual void mutate() {
    for (auto& i : m_data) i.mutate();
  };
  virtual void cross(int t_elite) {
    for (auto it = m_data.begin() + t_elite; it < m_data.end(); it += 2)
      if (it + 1 != m_data.end()) {
        (*it).cross(*(it + 1));
      }
  };
};

#endif
