
#include "check.hpp"
#include <iostream>
#include <iomanip>

void Check::add(const Product& product, int quantity) {
    positions_.emplace_back(product, quantity);
    total_ += product.price * quantity;
}

void Check::print(const std::string& paymentType, double paid) {
    std::cout << "--- ЧЕК ---\n";
    for (const auto& [p, q] : positions_) {
        std::cout << p.name << " x" << q << " = " << std::fixed << std::setprecision(2) << p.price * q << "\n";
    }
    std::cout << "Итого: " << total_ << "\n";
    std::cout << "Оплата: " << (paymentType == "cash" ? "Наличными" : "Картой") << "\n";
    if (paymentType == "cash") std::cout << "Сдача: " << std::fixed << std::setprecision(2) << (paid - total_) << "\n";
    std::cout << "---------------\n";
}

double Check::total() const { return total_; }
