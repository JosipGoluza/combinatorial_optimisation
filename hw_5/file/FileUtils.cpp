//
// Created by josip on 06/01/2025.
//

#include "FileUtils.h"

#include <fstream>

// TODO hardkorirano broj fileova iz foldera
constexpr int FILE_NUMBER_PER_FOLDER = 1000;

std::pair<int, int> parseFirstInstance(const string &file_string) {
    vector<string> instances;
    std::string line;

    int variable_number;
    int clauses_number;

    std::istringstream instanceStream(file_string);

    bool found_p_line = false;

    while (std::getline(instanceStream, line)) {
        if (line.empty() || (line[0] == 'c' && found_p_line == false)) {
            continue;
        }

        if (line[0] == 'p') {
            found_p_line = true;
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> temp >> variable_number >> clauses_number;
            clauses_number = clauses_number - 1;
        } else if (found_p_line) {
            continue;
        }
    }

    return {variable_number, clauses_number};
}

string create_unique_name(const string & folder_name, const string & file_name) {
    std::vector<std::string> folder_parts;
    std::istringstream folder_stream(folder_name);
    std::string part;
    while (std::getline(folder_stream, part, '/')) {
        folder_parts.push_back(part);
    }

    std::string first_part = folder_parts[2];
    std::string second_part = folder_parts[3];
    // divide second part by "-"
    std::vector<std::string> seconds_parts;
    std::istringstream second_stream(second_part);
    while (std::getline(second_stream, part, '-')) {
        seconds_parts.push_back(part);
    }

    // Extract the number after "wuf" and the second number
    std::string wuf_number = seconds_parts[0].substr(3);
    std::string second_number = seconds_parts[1];

    // here modify file name to extract file_name_number
    std::vector<std::string> file_parts;
    std::istringstream file_stream(file_name);
    while (std::getline(file_stream, part, '-')) {
        file_parts.push_back(part);
    }
    std::string file_name_number = file_parts[1].substr(0, file_parts[1].find('.'));

    std::string unique_name = first_part + "-" + wuf_number + "-" + second_number + "-" + file_name_number;

    return unique_name;
}

Example parseInstance(const string &file_string, const map<string, int>& solution_content, const string &folder_name, const string &file_name) {
    string unique_name = create_unique_name(folder_name, file_name);

    vector<string> instances;
    std::string line;

    std::string optimal_solution_name;
    std::vector<int> weights;
    std::vector<std::vector<int>> clauses;
    int optimal_solution;

    std::istringstream instanceStream(file_string);

    bool found_p_line = false;

    while (std::getline(instanceStream, line)) {
        if (line.empty() || (line[0] == 'c' && found_p_line == false)) {
            continue;
        }

        if (line[0] == 'p') {
            found_p_line = true;
            std::istringstream iss(line);
            std::string temp;
            iss >> temp >> temp >> temp >> temp;
        } else if (found_p_line) {
            if (line[0] == 'c') {
                if (line.substr(2, 3) == "SAT") {
                    std::istringstream iss(line);
                    std::string temp, file_name_parse;
                    iss >> temp >> temp >> temp >> file_name_parse;
                    size_t start = file_name_parse.find('/') + 1;
                    size_t end = file_name_parse.find('.');
                    optimal_solution_name = file_name_parse.substr(start, end - start);
                    if (solution_content.empty()) {
                        optimal_solution = 0;
                    } else {
                        if (!solution_content.contains(optimal_solution_name)) {
                            optimal_solution = 0;
                        } else {
                            optimal_solution = solution_content.at(optimal_solution_name);
                        }
                    }
                } else {
                    continue;
                }
            } else if (line[0] == 'w') {
                std::istringstream iss(line.substr(2));
                int weight;
                while (iss >> weight) {
                    weights.push_back(weight);
                }
                // remove last element which is 0
                weights.pop_back();
            } else {
                std::istringstream iss(line);
                std::vector<int> clause;
                int literal;
                while (iss >> literal) {
                    if (literal == 0) break;
                    clause.push_back(literal);
                }
                clauses.push_back(clause);
            }
        }
    }

    return {optimal_solution_name, weights, clauses, optimal_solution, unique_name};
}

Instance readFolderContent(const string & folder_name, const InstanceType instance_type, const map<string, int>& solution_content) {
    Instance instances;
    bool first_one = true;
    for (const auto& entry : std::filesystem::directory_iterator(folder_name)) {
        if (entry.is_regular_file()) {
            if (first_one) {
                string instance_content = readFileContent(entry.path().string());
                auto [fst, snd] = parseFirstInstance(instance_content);
                instances.variable_number = fst;
                instances.clauses_number = snd;
                instances.instance_type = instance_type;
                first_one = false;
            }
            string instance_content = readFileContent(entry.path().string());
            Example example = parseInstance(instance_content, solution_content, folder_name, entry.path().filename().string());
            instances.exampleList.push_back(example);
            if (instances.exampleList.size() == FILE_NUMBER_PER_FOLDER) {
                break;
            }
        }
    }
    return instances;
}

std::string readFileContent(const std::string &filepath) {
    const std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

map<string, int> readSolution(const string &file_name) {
    string file_content = readFileContent(file_name);
    vector<string> solutions;
    std::string line;
    map<string, int> solution_map;
    std::istringstream instanceStream(file_content);

    while (std::getline(instanceStream, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string instance_name;
        int optimal_solution;
        iss >> instance_name >> optimal_solution;
        solution_map[instance_name] = optimal_solution;
    }
    return solution_map;
}
