
#pragma once
#include <string>

class IMetric {
public:
    virtual std::string collect() = 0;
    virtual ~IMetric() = default;
};
