#include <iostream>
#include "population.h"
#include <fstream>

// Constructor definition
Population::Population() : gen(rd()) {}

// Set the size of the population
void Population::set_population_size(int pop_size) 
{
    population_size = pop_size;
}

// Create the individuals in the population
void Population::build_population()
{
    for (int i = 0; i < population_size; i++)
    {
        Bag bag;
        bag.randomize_bag();
        population_vector.push_back(bag);
    }
}

// Print the population
void Population::print_population()
{
    for (unsigned long i = 0; i < population_vector.size(); i++)
    {
        population_vector[i].print_bag();
    }
}

// Pseudorandomly select an individual from the top 50% fittest members of the population
Bag Population::randomly_select_solution()
{
    if (population_vector.empty()) 
    {
        throw std::runtime_error("Population is empty");
    }

    std::uniform_int_distribution<size_t> distrib(0, ((population_vector.size() - 1) / 2));
    size_t target_solution = distrib(gen);

    Bag bag = population_vector[target_solution];
    
    return bag;
}

// Given two parents, set a crossover point and create two children 
std::pair<Bag, Bag> Population::create_children(const Bag& parent1, const Bag& parent2)
{    
    std::uniform_int_distribution<> distrib(0, 11);
    int crossover_point = distrib(gen);

    Bag child1(parent1), child2(parent2);
    for (int i = crossover_point; i < 12; i++) 
    {
        std::swap(child1.return_array()[i], child2.return_array()[i]);
    }
    
    mutate(child1);
    mutate(child2);

    return {child1, child2};
}

// Sort the population and drive creation of the next generation 
void Population::evolve(int generation) 
{
    // Sort population by fitness
    std::sort(population_vector.begin(), population_vector.end(), 
    [](Bag& a, Bag& b) 
    { 
        return a.return_fitness() > b.return_fitness(); 
    });
    
    std::ofstream outfile;
    outfile.open("generation.txt", std::ios_base::app);

    outfile << "Generation #" << generation << std::endl;
    print_population();

    std::vector<Bag> new_generation;
    new_generation.reserve(population_size);

    // Keep the top 50% of the population
    new_generation.insert(new_generation.end(), 
        population_vector.begin(), 
        population_vector.begin() + population_size / 2);

    // Create children for the other 50%
    while ((int)new_generation.size() < population_size)
    {
        Bag parent1 = randomly_select_solution();
        Bag parent2 = randomly_select_solution();

        auto [child1, child2] = create_children(parent1, parent2);
        
        new_generation.push_back(child1);
        if ((int)new_generation.size() < population_size) 
        {
            new_generation.push_back(child2);
        }
    }

    population_vector = std::move(new_generation);
}

// Mutate individuals, with a 1 in 100 chance per bit
void Population::mutate(Bag& child) 
{
    std::uniform_int_distribution<> dis(0, 99);
    
    for (int i = 0; i < 12; i++) 
    {
        if (dis(gen) == 72) 
        {
            child.return_array()[i] = 1 - child.return_array()[i];
        }
    }
    
    child.determine_fitness();
}

// Clear the generation.txt file
void Population::clear_file()
{
    std::ofstream ofs;
    ofs.open("generation.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

// Select the fittest solution from the final generation
Bag Population::select_top_solution()
{
    std::vector<Bag> fittest_solutions;
    std::ofstream outfile;
    outfile.open("generation.txt", std::ios_base::app);
    outfile << "Fittest solution: ";

    fittest_solutions.push_back(population_vector[0]);

    int* fittest_array = population_vector[0].return_array();

    for (int i = 0; i < population_size; i++)
    {
        if (population_vector[i].return_fitness() == 
            population_vector[0].return_fitness())
            {
                int* compare_array = population_vector[i].return_array();
                for (int j = 0; j < fittest_solutions.size(); j++)
                {
                    int check{};
                    for (int p = 0; p < 12; p++)
                    {
                        if (fittest_array[p] == compare_array[p])
                        {
                            check++;
                        }
                        if (check != 12)
                        {
                            fittest_solutions.push_back(population_vector[i]);
                        }
                    }
                }
            }
    }

    outfile << "REEEEEEEE\n";

    for (int i = 0; i < fittest_solutions.size(); i++)
    {
        fittest_solutions[i].print_bag();
    }

    outfile << "REEEEEEEE\n";
    return population_vector[0];
}