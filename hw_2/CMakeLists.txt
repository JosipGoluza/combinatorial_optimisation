cmake_minimum_required(VERSION 3.29)
project(hw_2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
SET(CMAKE_BUILD_TYPE Debug)

add_executable(hw_2 main.cpp
        models.h
        branch_and_bound.h
        branch_and_bound.cpp
        file_utils.h
        file_utils.cpp
        main.h
        simple_heuristics/simple_heuristic.cpp
        simple_heuristics/simple_heuristic.h
        simple_heuristics/helper.cpp
        simple_heuristics/helper.h
        extended_heuristic/extended_heuristic.cpp
        extended_heuristic/extended_heuristic.h
        extended_heuristic/helper_extended.cpp
        extended_heuristic/helper_extended.h
        utils.cpp
        utils.h
        dynamic_programming/dynamic_programming.cpp
        dynamic_programming/dynamic_programming.h
        dynamic_programming/helper_dynamic.cpp
        dynamic_programming/helper_dynamic.h
        fptas/fptas_approximation.cpp
        fptas/fptas_approximation.h
        fptas/helper_fptas.cpp
        fptas/helper_fptas.h
)
