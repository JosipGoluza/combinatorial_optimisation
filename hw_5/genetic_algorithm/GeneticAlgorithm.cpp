//
// Created by josip on 06/01/2025.
//

#include "GeneticAlgorithm.h"

#include <filesystem>
#include <fstream>

// HARDKODIRANO
constexpr int VAR_NUM_IN_CLAUSE = 3;

MaxSatGA::MaxSatGA(Example example, const int pop_size, const int generations, const int tour_size, const int elites,
                   const int variable_number, const int clauses_number, const int max_attempts, const double cross_rate,
                   const double mut_rate, const ParameterChange parameter_changed, const double threshold)
    : population_size(pop_size),
      num_generations(generations),
      crossover_rate(cross_rate),
      mutation_rate(mut_rate),
      initial_mutation(mut_rate),
      tournament_size(tour_size),
      num_elites(elites),
      variable_number(variable_number),
      clauses_number(clauses_number),
      max_attempts(max_attempts),
      parameter_changed(parameter_changed),
      threshold(threshold),
      problem_instance(std::move(example)),
      rng(rd()) {
}

void MaxSatGA::onePointCrossover(Chromosome &parent1, Chromosome &parent2, std::mt19937 &rng) {
    std::uniform_int_distribution<> crossover_point(1, variable_number - 1);
    const int point = crossover_point(rng);

    // Swap genes after crossover point
    for (int i = point; i < variable_number; ++i) {
        const bool temp = parent1.genes[i];
        parent1.genes[i] = parent2.genes[i];
        parent2.genes[i] = temp;
    }
}

int MaxSatGA::calculateFitness(const Chromosome &chromosome) {
    const std::size_t hash_key = std::hash<std::vector<bool> >{}(chromosome.genes);

    auto it = fitness_cache.find(hash_key);
    if (it != fitness_cache.end()) {
        return it->second;
    }

    int fitness = 0;
    // Check clause satisfaction and sum weights
    for (const std::vector<int> &clause: problem_instance.clauses) {
        bool satisfied = false;
        for (const int literal: clause) {
            const int var_idx = abs(literal) - 1;
            const bool value = chromosome.genes[var_idx];
            if ((literal > 0 && value) || (literal < 0 && !value)) {
                satisfied = true;
                break;
            }
        }
        if (!satisfied) {
            return -1; // Penalize if any clause is unsatisfied
        }
    }

    for (size_t i = 0; i < chromosome.genes.size(); ++i) {
        if (chromosome.genes[i]) {
            fitness += problem_instance.weights[i];
        }
    }

    fitness_cache[hash_key] = fitness;

    return fitness;
}

Chromosome MaxSatGA::tournamentSelection() {
    std::vector<Chromosome> tournament;
    std::uniform_int_distribution<> dist(0, population_size - 1);

    for (int i = 0; i < tournament_size; ++i) {
        tournament.push_back(population[dist(rng)]);
    }

    return *ranges::max_element(tournament,
                                [](const Chromosome &a, const Chromosome &b) {
                                    return a.fitness < b.fitness;
                                });
}

double MaxSatGA::calculateAverageFitness() {
    double total_fitness = 0.0;
    for (const auto &chromosome: population) {
        total_fitness += chromosome.fitness;
    }
    return total_fitness / population_size;
}

void MaxSatGA::initializePopulation() {
    population.clear();
    population.reserve(population_size);
    for (int i = 0; i < population_size; ++i) {
        Chromosome chromosome(variable_number);
        chromosome.randomize(rng);
        chromosome.fitness = calculateFitness(chromosome);
        if (chromosome.fitness == -1) {
            repair(rng, chromosome);
        }
        chromosome.fitness = calculateFitness(chromosome);
        population.push_back(chromosome);
    }
}

pair<double, int> MaxSatGA::evolve() {
    initializePopulation();
    double previous_average_fitness = 0.0;
    int no_significant_change_count = 0;
    int max_no_change_generations = scaleClausesToMaxNoChange();

    int max_fitness;
    double current_average_fitness;


    for (int gen = 0; gen < num_generations; ++gen) {
        std::vector<Chromosome> new_population;


        for (size_t i = 0; i < population.size() / 2; ++i) {
            Chromosome parent1 = tournamentSelection();
            Chromosome parent2 = tournamentSelection();

            std::uniform_real_distribution<> dist(0, 1);
            if (dist(rng) < crossover_rate) {
                onePointCrossover(parent1, parent2, rng);
            }

            parent1.mutate(mutation_rate, rng);
            parent2.mutate(mutation_rate, rng);

            parent1.fitness = calculateFitness(parent1);
            parent2.fitness = calculateFitness(parent2);

            if (parent1.fitness == -1) {
                repair(rng, parent1);
                parent1.fitness = calculateFitness(parent1);
            }

            if (parent2.fitness == -1) {
                repair(rng, parent2);
                parent2.fitness = calculateFitness(parent2);
            }

            new_population.push_back(parent1);
            new_population.push_back(parent2);
        }

        std::vector<Chromosome> elites(num_elites);
        std::partial_sort_copy(population.begin(), population.end(), elites.begin(), elites.end(),
                               [](const Chromosome &a, const Chromosome &b) {
                                   return a.fitness > b.fitness;
                               });

        max_fitness = elites[0].fitness;

        ranges::copy(elites, new_population.begin());

        population = new_population;

        current_average_fitness = calculateAverageFitness();

        // Check for significant change in average fitness
        if (gen > 0) { // Skip the first generation
            double change = std::fabs(current_average_fitness - previous_average_fitness) / previous_average_fitness;

            if (change < threshold) {
                no_significant_change_count++;
            } else {
                no_significant_change_count = 0; // Reset counter if change is significant
            }

            // Check if we have reached the maximum number of generations without significant change
            if (no_significant_change_count >= max_no_change_generations) {
                //std::cout << "Stopping early due to convergence." << std::endl;
                best_fitnesses.push_back(max_fitness);
                average_fitnesses.push_back(current_average_fitness);
                break;
            }
        }

        previous_average_fitness = current_average_fitness;
        best_fitnesses.push_back(max_fitness);
        average_fitnesses.push_back(current_average_fitness);
        if (max_fitness == current_average_fitness && max_fitness > 1) {
            break;
        }
        calculate_new_mutation_rate(max_fitness, current_average_fitness, gen);
        if (gen % 10 == 0 && gen != 0) {
            // average has come to max fitness
            check_for_feasible(current_average_fitness, max_fitness);
        }

        /*std::cout << "Generation: " << gen << " Best fitness: " << max_fitness << " Average fitness: "
                  << current_average_fitness << std::endl;
        std::cout << "Population size: " << population_size << " Tournament size: " << tournament_size
                  << " Num elites: " << num_elites << " Max attempts: " << max_attempts << std::endl;

        std::cout << std::endl;*/
    }

    return pair(current_average_fitness, max_fitness);
}

void MaxSatGA::calculate_new_mutation_rate(const int max_fitness, const double average_fitness, const int gen) {
    //std::cout << "Mutation rate: " << mutation_rate << std::endl;
    auto fitness_ratio = average_fitness / max_fitness;
    if (average_fitness < 0) {
        return;
    } else if (fitness_ratio > 0.9) {
        mutation_rate = initial_mutation * (1 - average_fitness / max_fitness);
    } else {
        mutation_rate = initial_mutation * (1 - average_fitness / max_fitness) * (1 - static_cast<double>(gen) / num_generations);
    }
}

string MaxSatGA::get_type_number() const {
    switch (parameter_changed) {
        case NONE:
            return "";
        case POPULATION_SIZE:
            return std::to_string(population_size);
        case TOURNAMENT_SIZE:
            return std::to_string(tournament_size);
        case NUM_ELITES:
            return std::to_string(num_elites);
        case NUM_GENERATIONS:
            return std::to_string(num_generations);
        case MAX_ATTEMPTS:
            return std::to_string(max_attempts);
        case MUTATION_RATE:
            return std::to_string(initial_mutation);
        case CROSSOVER_RATE:
            return std::to_string(crossover_rate);
        case CHANGE_THRESHOLD:
            return std::to_string(threshold);
    }
    return "";
}

void MaxSatGA::create_csv_history() const {
    // Ensure the directory exists
    std::filesystem::create_directories("results/" + parameterChangeToFolder(parameter_changed) + "/measurements");
    const string type_number = get_type_number();

    std::ofstream file(
        "results/" + parameterChangeToFolder(parameter_changed) + "/measurements/" + problem_instance.unique_name + "-" + type_number +  "_history.csv");

    file << "generation,best_fitness,average_fitness,optimal_solution\n";

    for (int i = 0; i < average_fitnesses.size(); ++i) {
        file <<
                i << ","
                << best_fitnesses[i] << ","
                << average_fitnesses[i] << ","
                << problem_instance.optimal_solution << "\n";
    }
}

void MaxSatGA::repair(std::mt19937 &rng, Chromosome &chromosome) {
    int attempts = 0;
    while (calculateFitness(chromosome) == -1 && attempts < max_attempts) {
        for (const std::vector<int> &clause: problem_instance.clauses) {
            bool satisfied = false;
            for (const int literal: clause) {
                const int var_idx = abs(literal) - 1;
                const bool value = chromosome.genes[var_idx];
                if ((literal > 0 && value) || (literal < 0 && !value)) {
                    satisfied = true;
                    break;
                }
            }
            if (!satisfied) {
                // Flip a random bit in the clause
                std::uniform_int_distribution<> dist(0, VAR_NUM_IN_CLAUSE - 1);


                const int flip_idx = abs(clause[dist(rng)]) - 1;
                chromosome.genes[flip_idx] = !chromosome.genes[flip_idx];
                break;
            }
        }
        attempts++;
    }
}

int MaxSatGA::scaleClausesToMaxNoChange() const {
    constexpr int x_min = 78;
    constexpr int x_max = 430;
    constexpr int y_min = 20;
    constexpr int y_max = 100;

    if (clauses_number < x_min) {
        return y_min; // Return minimum if below the range
    } else if (clauses_number > x_max) {
        return y_max; // Return maximum if above the range
    } else {
        // Linear interpolation
        return y_min + static_cast<int>((static_cast<double>(clauses_number - x_min) / (x_max - x_min)) * (y_max - y_min));
    }
}

// TODO neke hardocirane stvari u ovoj metodi
constexpr double stuck_ratio = 0.5;

void MaxSatGA::check_for_feasible(const double current_average_fitness, const int max_fitness) {
    if (current_average_fitness < 0) {
        const int old_population_size = population_size;
        const int new_size = 5000;
        vector<Chromosome> new_population = population;
        while (new_population.size() < new_size) {
            Chromosome chromosome(variable_number);
            chromosome.randomize(rng);
            chromosome.fitness = calculateFitness(chromosome);
            if (chromosome.fitness == -1) {
                repair(rng, chromosome);
                chromosome.fitness = calculateFitness(chromosome);
            }
            new_population.push_back(chromosome);
        }
        population = std::move(new_population);
        population_size = new_size;
        max_attempts = 500;
        tournament_size = min(30, tournament_size + 10);
        num_elites = 3;
    } else if (population_size < 1000) {
        if (current_average_fitness / max_fitness < stuck_ratio) {
            tournament_size = max(3, tournament_size + 1);
            num_elites = max(3, num_elites + 1);
        } else if (current_average_fitness / max_fitness > stuck_ratio) {
            tournament_size = max(4, tournament_size + 1);
            num_elites = max(3, num_elites + 1);
        } else if (current_average_fitness / max_fitness > 0.7) {
            tournament_size = max(6, tournament_size + 1);
            num_elites = max(3, num_elites + 1);
        } else if (current_average_fitness / max_fitness > 0.9) {
            tournament_size = max(8, tournament_size + 1);
            num_elites = max(4, num_elites + 1);
        }
    } else {
        // big instance, want to converge faster
        if (current_average_fitness / max_fitness < stuck_ratio) {
            tournament_size = min(100, tournament_size + 10);
            num_elites = min(6, num_elites + 1);
        } else if (current_average_fitness / max_fitness > stuck_ratio) {
            tournament_size = min(120, tournament_size + 10);
            num_elites = min(6, num_elites + 1);
        } else if (current_average_fitness / max_fitness > 0.7) {
            tournament_size = min(130, tournament_size + 10);
            num_elites = min(7, num_elites + 1);
        } else if (current_average_fitness / max_fitness > 0.9) {
            tournament_size = min(140, tournament_size + 10);
            num_elites = min(7, num_elites + 1);
        }
    }
}