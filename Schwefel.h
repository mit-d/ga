#ifndef _SCHWEFEL_H_
#define _SCHWEFEL_H_

#include <algorithm>
#include <numeric>

namespace ga {
template <typename InputIterator>
inline double sch(InputIterator begin, InputIterator end) {
    return 418.9829 * static_cast<double>(end - begin) +
           std::accumulate(begin, end, 0.0, [](double t, double d) -> double {
               return (t + d * sin(sqrt(abs(d))));
           });
}
}  // namespace ga
#endif
