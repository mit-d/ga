
#include <iostream>
#include "Chrom.h"
#include "Population.h"

using namespace std;

int main() {
    ga::Chrom left(6);
    left.range(0, 10).randomize();
    ga::Chrom right(6);
    right.range(0, 10).randomize();

    left.print();
    right.print();

    left.cross(right);

    cout << endl << "Test genome functionality" << endl;
    left.print();
    right.print();
    right.mutate();
    right.print();

    cout << endl << "Test population functionality" << endl;
    std::vector<ga::Chrom> population(10, ga::Chrom(5));
    for (auto& i : population) i.range(-1, 1).randomize();
    for (auto& i : population) cout << i << endl;
    ga::cross(population.begin(), population.end());
    cout << endl;
    for (auto& i : population) cout << i << endl;
}
