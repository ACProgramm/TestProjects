
#pragma once
#include "metric.hpp"
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

class MemoryMetric : public IMetric {
public:
    explicit MemoryMetric(const std::vector<std::string>& specs)
        : specs_(specs) {}

    std::string collect() override {
        std::ifstream meminfo("/proc/meminfo");
        std::string line;
        std::unordered_map<std::string, long> mem_data;

        while (std::getline(meminfo, line)) {
            std::istringstream iss(line);
            std::string key;
            long value;
            std::string kb;
            iss >> key >> value >> kb;
            key = key.substr(0, key.size() - 1);
            mem_data[key] = value;
        }

        long total = mem_data["MemTotal"];
        long available = mem_data["MemAvailable"];
        long free = mem_data["MemFree"];
        long used = total - available;

        std::ostringstream oss;
        for (const auto& spec : specs_) {
            if (spec == "used") {
                oss << "Memory used: " << used / 1024 << " MB\n";
            } else if (spec == "free") {
                oss << "Memory free: " << free / 1024 << " MB\n";
            }
        }

        return oss.str();
    }

private:
    std::vector<std::string> specs_;
};
