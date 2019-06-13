#ifndef _RASTRAGIN_H_
#define _RASTRAGIN_H_

#include "Chrom.h"

namespace ga {
template <typename ForwardIterator>
inline double ras(ForwardIterator begin, ForwardIterator end) {
   return (10.0 * static_cast<double>(end - begin)) +
          std::accumulate(begin, end, 0.0, [](double t, double d) -> double {
             return (t + pow(d, 2.0) - 10.0 * cos(2.0 * M_PI * d));
          });
}

class Rastragin : public Chrom {
  public:
   Rastragin() : Rastragin(10){};
   Rastragin(size_t sz) : Chrom({-5.12, 5.12}, sz){};
   ~Rastragin(){};
   double fitness() const { return ras(cbegin(), cend()); }
};
}  // namespace ga
#endif
