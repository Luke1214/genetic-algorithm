#include <iostream>
#include <vector>
#include <random>

const unsigned int values[12] = {6, 5, 8, 7, 6, 9, 4, 5, 4, 9, 2, 1};
const unsigned int weights[12] = {20, 30, 60, 90, 50, 70, 30, 30, 70, 20, 20, 60};

class Bag {
public:
    // Constructor
    Bag();

    // Mutators
    void randomize_bag();
    void set_value(int given_value);
    void determine_weight();
    void determine_value();
    void determine_fitness();
    void set_index(int input_index);

    // Accessors
    void print_bag();
    int return_value();
    int return_fitness();
    int* return_array();
    int get_index();

private:
    int items_in_bag[12];
    int value{};
    int weight{};
    bool overweight = false;
    int fitness{};
    int index{};
};