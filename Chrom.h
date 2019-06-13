#ifndef _chrom_h_
#define _chrom_h_

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
  Chrom(std::pair<double, double> t_range, size_t n)
      : m_min(t_range.first),
        m_max(t_range.second),
        m_data(std::vector<double>(n, ((m_max - m_min) / 2.0))){};
  Chrom(size_t n) : Chrom({0, 0}, n){};
  Chrom() : Chrom({0, 0}, 0){};
  virtual ~Chrom(){};

 private:  // Member Data
  std::string m_name{""};
  double m_min = 0.0, m_max = 0.0;
  std::vector<double> m_data{};

 public:  // Operator Overloads
  bool operator>(const Chrom &t_chrom) const {
    return fitness() > t_chrom.fitness();
  };
  bool operator<(const Chrom &t_chrom) const {
    return fitness() < t_chrom.fitness();
  };

 protected:  // Data iterators
  auto begin() { return m_data.begin(); };
  auto end() { return m_data.end(); };
  auto rbegin() { return m_data.rbegin(); };
  auto rend() { return m_data.rend(); };
  auto cbegin() const { return m_data.cbegin(); };
  auto cend() const { return m_data.cend(); };
  auto crbegin() const { return m_data.crbegin(); };
  auto crend() const { return m_data.crend(); };
  auto size() const { return m_data.size(); };

 public:  // Member Functions
  double dist2(const Chrom &t_other) const {
    std::vector<double> aux;
    std::transform(cbegin(), cend(), t_other.cbegin(), std::back_inserter(aux),
                   [](double l, double r) { return pow((l - r), 2); });
    aux.shrink_to_fit();
    return sqrt(std::accumulate(aux.begin(), aux.end(), 0.0));
  }
  void randomize() {
    std::uniform_real_distribution udistr(m_min, m_max);
    for (auto &i : m_data) i = udistr(ga::rng);
  };
  std::string name() { return m_name; };
  const std::pair<double, double> range() { return std::tie(m_min, m_max); };
  void print() {
    std::cout << std::fixed << std::setw(9) << fitness() << std::setw(2);
    std::cout << "{" << *this << "}" << std::endl;
  };
  void set_data(std::vector<double> t_vector) { m_data = t_vector; };
  void set_range(const std::pair<double, double> t_range) {
    m_min = t_range.first;
    m_max = t_range.second;
  };
  const std::vector<double> &data() const { return m_data; };

 public:  // Genetic Operators
  /* double fitness() const { return 0.0; }; */
  virtual double fitness() const {
    return std::accumulate(cbegin(), cend(), 0.0);
  }
  virtual void cross(Chrom &t_other) {
    std::uniform_int_distribution<size_t> udist(0, size() - 1);
    std::swap_ranges(begin(), begin() + udist(rng), t_other.begin());
  };
  virtual void mutate() {
    static const double std_dev = .1;
    std::uniform_int_distribution<size_t> udistr(0, size() - 1);
    std::normal_distribution ndistr(0.0, std_dev);

    /* std::uniform_int_distribution<size_t> sel(0, 2); */

    auto choice = udistr(rng);

    m_data[choice] += pow(ndistr(rng), 5);

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
