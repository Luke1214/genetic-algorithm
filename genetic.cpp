#include <iostream>
#include <vector>
#include "population.h"

int main()
{
    Population population;
    population.clear_file();
    population.set_population_size(200);
    population.build_population();
    
    for (int i = 0; i < 25; i++)
    {
        population.evolve(i);
    }

    Bag bag = population.select_top_solution();
    bag.print_bag();
}