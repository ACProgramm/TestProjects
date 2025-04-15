
#include "shift.hpp"
#include <iostream>
#include <iomanip>

Shift::Shift(const std::string& cashierName, double cashStart)
    : cashier_(cashierName), cashStart_(cashStart), totalCash_(0), totalCard_(0) {}

void Shift::addCash(double amount) { totalCash_ += amount; }
void Shift::addCard(double amount) { totalCard_ += amount; }

void Shift::printSummary() {
    std::cout << "--- Смена закрыта ---\nКассир: " << cashier_ << "\nИтог по оплатам:\n";
    std::cout << "  Наличные: " << std::fixed << std::setprecision(2) << totalCash_ << "\n";
    std::cout << "  Карта: " << std::fixed << std::setprecision(2) << totalCard_ << "\n---------------\n";
}
