
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class ConfigLoader {
public:
    explicit ConfigLoader(const std::string& path) {
        std::ifstream file(path);
        nlohmann::json j;
        file >> j;

        period = std::stoi(j["settings"]["period"].get<std::string>());

        for (auto& m : j["metrics"]) {
            if (m["type"] == "cpu") {
                for (auto id : m["ids"]) {
                    cpu_ids.push_back(id.get<int>());
                }
            } else if (m["type"] == "memory") {
                for (auto& spec : m["spec"]) {
                    memory_specs.push_back(spec.get<std::string>());
                }
            }
        }
    }

    int get_period() const { return period; }
    const std::vector<int>& get_cpu_ids() const { return cpu_ids; }
    const std::vector<std::string>& get_memory_specs() const { return memory_specs; }

private:
    int period = 5;
    std::vector<int> cpu_ids;
    std::vector<std::string> memory_specs;
};
