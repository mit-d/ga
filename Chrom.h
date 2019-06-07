#ifndef _crom_h_
#define _crom_h_

#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace ga {
static std::random_device rd;
static std::mt19937_64 rng(rd());

class Chrom {
  friend std::ostream &operator<<(std::ostream &t_stream, const Chrom &t_obj);

 public:  // Constructors and Deconstructors
  Chrom(){};
  Chrom(const std::vector<double> t_data) : m_data(t_data){};
  Chrom(const size_t t_n_genes, const double t_value)
      : m_range({t_value, t_value}),
        m_data(std::vector<double>(t_n_genes, t_value)){};
  Chrom(const size_t t_n_genes) : Chrom(t_n_genes, 0.0){};
  Chrom(const size_t t_n_genes, const double t_min, const double t_max)
      : m_data(std::vector<double>(t_n_genes, 0.0)) {
    randomize(t_min, t_max);
  };
  virtual ~Chrom(){};

 private:  // Member Data
  std::string m_name{""};
  std::tuple<double, double> m_range{0.0, 0.0};
  std::vector<double> m_data{};

 public:  // Operator Overloads
  bool operator<(const Chrom &t_chrom) const {
    return fitness() < t_chrom.fitness();
  };

 public:  // Member Functions
  void randomize(const double t_min, const double t_max) {
    m_range = std::make_tuple(t_min, t_max);
    std::uniform_real_distribution udistr(t_min, t_max);
    for (auto &i : m_data) i = udistr(ga::rng);
  };

  void name(const std::string t_string) { m_name = t_string; };
  std::string name() { return m_name; };
  const std::tuple<double, double> &range() { return m_range; };
  void range(const std::tuple<double, double> t_range) { m_range = t_range; };
  void print() {
    std::cout << std::fixed << std::setw(9) << fitness() << std::setw(2);
    std::cout << *this << std::endl;
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
  t_stream << t_obj.m_name << "{";
  for (const auto &i : t_obj.m_data)
    t_stream << std::setw(9) << std::fixed << i << ",";
  t_stream << "\b }";
  return t_stream;
}
}  // namespace ga

#endif  // _crom_h_
