cmake_minimum_required(VERSION 3.10)

# Define the project name and specify that it uses C++
project(GeneticAlgorithm LANGUAGES CXX)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
add_compile_options(-Wall -Wextra)

# Define the source files
set(SOURCES genetic.cpp population.cpp bag.cpp)

# Define the executable from the specified source files
add_executable(genetic ${SOURCES})