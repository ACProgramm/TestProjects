
#include <iostream>
#include <thread>
#include <chrono>
#include "config.hpp"
#include "metrics/cpu_metric.hpp"
#include "metrics/memory_metric.hpp"
#include "output/console_output.hpp"

int main() {
    ConfigLoader config("config.json");

    int period = config.get_period();
    std::vector<std::unique_ptr<IMetric>> metrics;

    for (const auto& cpu_id : config.get_cpu_ids()) {
        metrics.emplace_back(std::make_unique<CpuMetric>(cpu_id));
    }

    if (!config.get_memory_specs().empty()) {
        metrics.emplace_back(std::make_unique<MemoryMetric>(config.get_memory_specs()));
    }

    ConsoleOutput output;

    while (true) {
        std::string all_data;
        for (const auto& metric : metrics) {
            all_data += metric->collect() + "\n";
        }
        output.write(all_data);
        std::this_thread::sleep_for(std::chrono::seconds(period));
    }

    return 0;
}
