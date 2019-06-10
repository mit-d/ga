#ifndef _ga_h_
#define _ga_h_

#include <vector>
#include "Chrom.h"

namespace ga {

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

}  // namespace ga
#endif  // #define _ga_h_
