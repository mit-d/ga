#ifndef _SPHERICAL_H_
#define _SPHERICAL_H_

#include "Chrom.h"

namespace ga {

template <typename InputIterator>
inline double sph(InputIterator begin, InputIterator end) {
  return std::accumulate(begin, end, 0.0, [](double t, double d) -> double {
    return t + pow(d, 2);
  });
}

class Spherical : public Chrom {
 public:
  Spherical() : Spherical(10){};
  Spherical(size_t sz) : Chrom({-5.12, 5.12}, sz){};
  ~Spherical(){};
  double fitness() const { return sph(cbegin(), cend()); }
};

}  // namespace ga
#endif
