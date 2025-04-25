cmake_minimum_required(VERSION 3.29)
project(hw_4)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
#SET(CMAKE_BUILD_TYPE Debug) # for debugging

include_directories(.)
include_directories(model)

add_executable(hw_4
        model/Instance.h
        main.cpp
        main.h
        model/Item.h
        model/Example.h
        model/Result.h
        file/read_file.h
        file/read_file.cpp
        file/read_file.h
        file/file_utils.cpp
        file/file_utils.h
        algorith_properties/fill_properties.cpp
        algorith_properties/fill_properties.h
        genetic_algorithm/helper_genetic.cpp
        genetic_algorithm/helper_genetic.h
        genetic_algorithm/calculate_genetic.cpp
        genetic_algorithm/calculate_genetic.h
        chromosome/chromosome.cpp
        genetic_algorithm/knapsack_ga.cpp
        chromosome/chromosome.h
        genetic_algorithm/knapsack_ga.h
)
