cmake_minimum_required(VERSION 3.29)
project(hw_5)

set(CMAKE_CXX_STANDARD 20)

# Enable optimizations for MSVC
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /GL /Gy")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    add_compile_options(/MP)
endif()

# Enable Unity builds
set(CMAKE_UNITY_BUILD ON)

# Release mode
set(CMAKE_BUILD_TYPE Release)
add_compile_definitions(NDEBUG)

add_executable(hw_5 main.cpp
        model/Instance.h
        file/ReadFile.cpp
        file/ReadFile.h
        main.h
        file/FileUtils.cpp
        file/FileUtils.h
        model/Algorithm.h
        algorithm_properties/FillProperties.cpp
        algorithm_properties/FillProperties.h
        model/Result.h
        helper/HelperGenetic.cpp
        helper/HelperGenetic.h
        genetic_algorithm/GeneticAlgorithm.cpp
        genetic_algorithm/GeneticAlgorithm.h
        genetic_algorithm/Chromosome.cpp
        genetic_algorithm/Chromosome.h
        csv/CreateCsvs.cpp
        csv/CreateCsvs.h
        thread_pool/ThreadPool.cpp
        thread_pool/ThreadPool.h)