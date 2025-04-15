
#pragma once
#include <string>

class IOutput {
public:
    virtual void write(const std::string& data) = 0;
    virtual ~IOutput() = default;
};
