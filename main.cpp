#include <cmath>
#include <iostream>
#include "Chrom.h"
/* #include "Population.h" */

using namespace std;

int main() {
    /* vector<ga::Chrom> population(5, ga::Chrom(5)); */
    /* for (auto& i : population) i.randomize(-1, 1); */
    /* std::sort(population.begin(), population.end()); */

    /* for (int i = 0; i < 100; ++i) { */
    /* } */

    /* for (auto it = population.begin(); it != population.end(); ++it) { */
    /*     static int zzz = 0; */
    /*     ++zzz; */
    /*     /1* cout << "vec[" << zzz << "]" << *it << endl; *1/ */
    /*     (*it).print(); */
    /* } */

    ga::Chrom left(6);
    left.randomize(0, 10);
    ga::Chrom right(6);
    right.randomize(-10, 0);

    left.print();
    right.print();

    left.cross(right);

    left.print();
    right.print();
    right.mutate();
    right.print();
}
