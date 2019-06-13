#ifndef _ACKLEY_H_
#define _ACKLEY_H_

#include <algorithm>
#include <cmath>
#include <numeric>

namespace ga {
template <typename ForwardIterator>
inline double ack(ForwardIterator begin, ForwardIterator end) {
    return (
        20.0 + M_E -
        20.0 *
            exp(-0.2 * sqrt((1.0 / static_cast<double>(end - begin)) *
                            std::accumulate(begin, end, 0.0,
                                            [](double t, double d) -> double {
                                                return (t + pow(d, 2));
                                            }))) -
        exp((1.0 / static_cast<double>(end - begin)) *
            std::accumulate(begin, end, 0.0, [](double t, double d) -> double {
                return (t + cos(2.0 * M_PI * d));
            })));
}
}  // namespace ga
#endif  // _ACKLEY_H_
