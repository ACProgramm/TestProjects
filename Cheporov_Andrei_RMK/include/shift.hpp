
#pragma once
#include <string>

class Shift {
public:
    Shift(const std::string& cashierName, double cashStart);
    void addCash(double amount);
    void addCard(double amount);
    void printSummary();

private:
    std::string cashier_;
    double cashStart_;
    double totalCash_;
    double totalCard_;
};
