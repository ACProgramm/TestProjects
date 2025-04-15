
#pragma once
#include "product.hpp"
#include <vector>
#include <string>

class Check {
public:
    void add(const Product& product, int quantity);
    void print(const std::string& paymentType, double paid);
    double total() const;

private:
    std::vector<std::pair<Product, int>> positions_;
    double total_ = 0;
};
