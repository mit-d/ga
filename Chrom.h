#ifndef _crom_h_
#define _crom_h_

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

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

 public:  // Evolutionary
  virtual double fitness() const {
    return std::accumulate(m_data.begin(), m_data.end(), 0.0) /
           static_cast<double>(m_data.size());
  };
  virtual void cross(Chrom &t_other) {
    std::bernoulli_distribution coin(.5);
    auto t_it = t_other.m_data.begin();
    auto m_it = m_data.begin();

    // Uniform p(.5)
    while (m_it < m_data.end() && t_it < t_other.m_data.end()) {
      if (coin(rng)) std::swap(*m_it, *t_it);
      ++m_it;
      ++t_it;
    }
  };
  // Normal mean 0 std_dev .2
  virtual void mutate() {
    std::normal_distribution ndistr(0.0, 0.2);
    for (auto &i : m_data) i += ndistr(rng);
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

#endif  // _crom_h_
