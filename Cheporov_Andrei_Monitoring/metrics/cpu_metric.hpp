
#pragma once
#include "metric.hpp"
#include <fstream>
#include <sstream>
#include <unistd.h>

class CpuMetric : public IMetric {
public:
    explicit CpuMetric(int id) : core_id(id), prev_idle(0), prev_total(0) {
        update_prev();
    }

    std::string collect() override {
        std::ifstream stat("/proc/stat");
        std::string line;
        for (int i = 0; i <= core_id && std::getline(stat, line);) {
            if (line.rfind("cpu" + std::to_string(core_id), 0) == 0) {
                std::istringstream iss(line);
                std::string label;
                unsigned long user, nice, system, idle, iowait, irq, softirq, steal;

                iss >> label >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
                unsigned long idle_time = idle + iowait;
                unsigned long non_idle = user + nice + system + irq + softirq + steal;
                unsigned long total = idle_time + non_idle;

                unsigned long totald = total - prev_total;
                unsigned long idled = idle_time - prev_idle;

                prev_total = total;
                prev_idle = idle_time;

                float usage = (totald - idled) * 100.0f / totald;
                return "CPU[" + std::to_string(core_id) + "] usage: " + std::to_string(usage).substr(0, 5) + "%";
            }
        }
        return "CPU[" + std::to_string(core_id) + "] data unavailable";
    }

private:
    int core_id;
    unsigned long prev_idle, prev_total;

    void update_prev() {
        std::ifstream stat("/proc/stat");
        std::string line;
        for (int i = 0; i <= core_id && std::getline(stat, line);) {
            if (line.rfind("cpu" + std::to_string(core_id), 0) == 0) {
                std::istringstream iss(line);
                std::string label;
                unsigned long user, nice, system, idle, iowait, irq, softirq, steal;
                iss >> label >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
                prev_idle = idle + iowait;
                prev_total = prev_idle + user + nice + system + irq + softirq + steal;
                break;
            }
        }
    }
};
