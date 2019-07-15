#ifndef _ROSENBROCK_H_
#define _ROSENBROCK_H_

#include "Chrom.h"

namespace ga {

template <typename InputIterator>
inline double ros(InputIterator begin, InputIterator end) {
  double rval = 0.0;
  for (auto it = begin; it + 1 < end; it += 1) {
    auto x_i = *it;
    auto x_ii = *(it + 1);
    rval += 100.0 * (pow(x_ii - pow(x_i, 2.0), 2.0) + pow(x_i - 1.0, 2.0));
  }
  return rval;
}

class Rosenbrock : public Chrom {
 public:
  Rosenbrock() : Rosenbrock(10){};
  Rosenbrock(size_t t_sz) : Chrom({-2.048, 2.048}, t_sz){};
  ~Rosenbrock(){};
  double fitness() const { return ros(cbegin(), cend()); }
};
}  // namespace ga
#endif
