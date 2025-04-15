
#pragma once
#include "product.hpp"
#include <map>
#include <string>

class ProductDB {
public:
    void load(const std::string& path);
    Product find(const std::string& query);

private:
    std::map<std::string, Product> byName_;
    std::map<std::string, Product> byCode_;
};
