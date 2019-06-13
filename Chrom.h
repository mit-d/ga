#ifndef _chrom_h_
#define _chrom_h_

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>
#include "fn.h"

namespace ga {
static std::random_device rd;
static std::mt19937_64 rng(rd());

class Chrom {
  friend std::ostream &operator<<(std::ostream &t_stream, const Chrom &t_obj);

 public:  // Constructors and Deconstructors
  Chrom(size_t n, double t_min, double t_max)
      : m_min(t_min),
        m_max(t_max),
        m_data(std::vector(n, (t_max - t_min) / 2)){};
  Chrom(size_t n, double t_val) : Chrom(n, t_val, t_val){};
  Chrom(size_t n) : Chrom(n, 0.0){};
  Chrom() : Chrom(30){};
  virtual ~Chrom(){};

 private:  // Member Data
  std::string m_name{""};
  double m_min = 0, m_max = 0;
  std::vector<double> m_data{};

 public:  // Operator Overloads
  bool operator<(const Chrom &t_chrom) const {
    return fitness() < t_chrom.fitness();
  };

 protected:  // Return vector iterators
  auto begin() { return m_data.begin(); };
  auto end() { return m_data.end(); };
  auto rbegin() { return m_data.rbegin(); };
  auto rend() { return m_data.rend(); };
  auto cbegin() const { return m_data.cbegin(); };
  auto cend() const { return m_data.cend(); };
  auto crbegin() const { return m_data.crbegin(); };
  auto crend() const { return m_data.crend(); };
  size_t size() const { return m_data.size(); };

 public:  // Member Functions
  void randomize() {
    std::uniform_real_distribution udistr(m_min, m_max);
    for (auto &i : m_data) i = udistr(ga::rng);
  };
  void name(const std::string t_string) { m_name = t_string; };
  std::string name() { return m_name; };
  const std::tuple<double, double> range() { return std::tie(m_min, m_max); };
  Chrom &range(double t_min, double t_max) {
    m_min = t_min;
    m_max = t_max;
    return *this;
  };
  void print() {
    std::cout << std::fixed << std::setw(9) << fitness() << std::setw(2);
    std::cout << "{" << *this << "}" << std::endl;
  };

 public:  // Genetic Operators
  virtual double fitness() const {
    /* return sph(m_data); */
    /* return ros(m_data); */
    /* return ras(m_data); */
    return ack(m_data);
  };
  virtual void cross(Chrom &t_other) {
    std::uniform_int_distribution<size_t> udist(0, size() - 1);
    std::swap_ranges(begin(), begin() + udist(rng), t_other.begin());
  };
  double dist2(Chrom &t_other) {
    std::vector<double> aux;
    std::transform(begin(), end(), t_other.begin(), std::back_inserter(aux),
                   [](double l, double r) { return pow((l - r), 2); });
    aux.shrink_to_fit();
    return sqrt(std::accumulate(aux.begin(), aux.end(), 0.0));
  }
  virtual void mutate() {
    static const double std_dev = .1;
    std::uniform_int_distribution<size_t> udistr(0, size() - 1);
    std::normal_distribution ndistr(0.0, std_dev);

    std::uniform_int_distribution<size_t> sel(0, 2);

    auto choice = udistr(rng);

    switch (sel(rng)) {
      case 0:
        m_data[choice] += pow(ndistr(rng), 5);
        break;
      case 1:
        /* std::iter_swap(begin() + udistr(rng), begin() + udistr(rng)); */
        /* break; */
        [[fallthrough]];
      case 2:
        [[fallthrough]];
      default:
        m_data[choice] += ndistr(rng);
        break;
    }

    // Adjust if OOB
    if (m_data[choice] > m_max) m_data[choice] = m_max;
    if (m_data[choice] < m_min) m_data[choice] = m_min;
  };
};

std::ostream &operator<<(std::ostream &t_stream, const Chrom &t_obj) {
  for (auto it = t_obj.m_data.begin(); it != t_obj.m_data.end(); ++it) {
    t_stream << *it;
    if (it != t_obj.m_data.end() - 1) t_stream << ",";
  }
  return t_stream;
}
}  // namespace ga

#endif  // _chrom_h_
