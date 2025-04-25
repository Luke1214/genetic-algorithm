#include <iostream>
#include <vector>
#include <stack>
#include "bag.h"

class Population {
public:
    // Constructor
    Population();

    // Mutators
    void set_population_size(int pop_size);
    void build_population();
    void print_population();
    Bag randomly_select_solution();
    std::pair<Bag, Bag> create_children(const Bag& parent1, const Bag& parent2);
    void evolve(int generation);
    void mutate(Bag& child);
    void clear_file();
    
    // Accessors
    Bag select_top_solution();

private:
    std::vector<Bag> population_vector;
    int population_size{};
    std::random_device rd;
    std::mt19937 gen;
};
