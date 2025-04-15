
#include "product_db.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

void ProductDB::load(const std::string& path) {
    std::ifstream f(path);
    nlohmann::json j;
    f >> j;
    for (auto& item : j) {
        Product p{item["name"], item["barcode"], item["price"]};
        byName_[p.name] = p;
        byCode_[p.barcode] = p;
    }
}

Product ProductDB::find(const std::string& query) {
    if (byCode_.count(query)) return byCode_[query];
    if (byName_.count(query)) return byName_[query];
    throw std::runtime_error("Товар не найден");
}
