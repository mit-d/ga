#ifndef _fn_h_
#define _fn_h_

#include <algorithm>  // std::accumulate()
#include <cmath>      // M_PI

inline double sph(const std::vector<double>& v) {
    return std::accumulate(
        v.cbegin(), v.cend(), 0.0,
        [](double t, double d) -> double { return t + pow(d, 2); });
}

struct sph_f {
    double operator()(const std::vector<double>& v) {
        return std::accumulate(
            v.cbegin(), v.cend(), 0.0,
            [](double t, double d) -> double { return t + pow(d, 2); });
    }
    double min = -5.12;
    double max = 5.12;
};

inline double ros(const std::vector<double>& v) {
    std::vector<double> tmp;
    double rval = 0.0;
    for (auto it = v.cbegin(); it + 1 < v.cend(); it += 1) {
        auto x_i = *it;
        auto x_ii = *(it + 1);
        rval += 100 * (pow(x_ii - pow(x_i, 2), 2) + pow(x_i - 1, 2));
    }
    return rval;
}

inline double ras(const std::vector<double>& v) {
    return (10.0 * v.size()) +
           std::accumulate(
               v.cbegin(), v.cend(), 0.0, [](double t, double d) -> double {
                   return (t + pow(d, 2.0) - 10.0 * cos(2.0 * M_PI * d));
               });
}

inline double sch(const std::vector<double>& v) {
    return 418.9829 * v.size() +
           std::accumulate(v.cbegin(), v.cend(), 0.0,
                           [](double t, double d) -> double {
                               return (t + d * sin(sqrt(abs(d))));
                           });
}
inline double schDS(const std::vector<double>& v) {
    return std::accumulate(v.cbegin(), v.cend(), 0.0,
                           [](double t, double d) -> double { return t * d; });
}

inline double ack(const std::vector<double>& v) {
    return (20.0 + M_E - 20.0 * exp(-0.2 * sqrt((1.0 / v.size()) * sph(v))) -
            exp((1.0 / v.size()) *
                std::accumulate(v.cbegin(), v.cend(), 0.0,
                                [](double t, double d) -> double {
                                    return (t + cos(2.0 * M_PI * d));
                                })));
}

// inline double gri(const std::vector<double>& v) {
//     return std::accumulate(v.cbegin(), v.cend(), 0.0,
//                            [](double t, double d) -> double { return t * d;
//                            });
// }

#endif
