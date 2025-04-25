#include <iostream>
#include <vector>
#include "bag.h"
#include <fstream>

Bag::Bag() {}

// Create an individual solution that contains random items
void Bag::randomize_bag()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, 1);

    //  Populate bag
    for (int i = 0; i < 12; i++)
    {
        int flip = distrib(gen);

        if (flip == 1)
            items_in_bag[i] = 1;
        else
            items_in_bag[i] = 0;
    }

    determine_fitness();
}

// Calculate the weight of the individual
void Bag::determine_weight()
{
    weight = 0;
    for (int i = 0; i < 12; i++)
    {
        if (items_in_bag[i] == 1)
            weight+=weights[i];
    }
    if (weight > 250)
    {
        overweight = true;
    }
    else
    {
        overweight = false;
    }
}

// Calculate the value (importance) of the individual
void Bag::determine_value()
{
    value = 0;
    for (int i = 0; i < 12; i++)
    {
        if (items_in_bag[i] == 1)
            value+=values[i];
    }
}

// Print the solution
void Bag::print_bag()
{
    std::ofstream outfile;
    outfile.open("generation.txt", std::ios_base::app);

    for (int i = 0; i < 12; i++)
    {
        outfile << items_in_bag[i];
    }
    outfile << " - value: " << value << ", fitness: " << fitness << ", weight: " << weight << std::endl;
}

// Calculate the fitness of an individual
void Bag::determine_fitness()
{
    determine_weight();
    determine_value();
    // Maximum allowable weight
    const int MAX_WEIGHT = 250;
    // Penalty for each unit of weight over the limit
    const int PENALTY_RATE = 10; 

    if (weight > MAX_WEIGHT) 
    {
        // Apply a penalty for exceeding weight limit
        fitness = value - (weight - MAX_WEIGHT) * PENALTY_RATE;
    } 
    else 
    {
        // No penalty if under or at weight limit
        fitness = value;
    }
}

void Bag::set_value(int given_value)
{
   value = given_value;
}

int Bag::return_value()
{
    return value;
}

int Bag::return_fitness()
{
    return fitness;
}

int* Bag::return_array()
{
    return items_in_bag;
}

void Bag::set_index(int input_index)
{
    index = input_index;
}

int Bag::get_index()
{
    return index;
}