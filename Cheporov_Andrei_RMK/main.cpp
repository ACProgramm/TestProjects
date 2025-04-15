
#include "include/product_db.hpp"
#include "include/check.hpp"
#include "include/shift.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

int main() {
    ProductDB db;
    db.load("products.json");

    std::string cashier;
    double startCash;
    std::cout << "Открытие смены\nВведите имя кассира: ";
    std::getline(std::cin, cashier);
    std::cout << "Введите стартовую наличность: ";
    std::cin >> startCash;
    std::cin.ignore();

    Shift shift(cashier, startCash);

    while (true) {
        std::cout << "\n--- Команды ---\n1. Новый чек\n2. Закрыть смену\n> ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "1") {
            Check check;
            while (true) {
                std::cout << "Введите штрих-код или имя товара: ";
                std::string q;
                std::getline(std::cin, q);
                try {
                    Product p = db.find(q);
                    std::cout << "Товар: " << p.name << ", Цена: " << p.price << "\nКоличество: ";
                    int qty;
                    std::cin >> qty;
                    std::cin.ignore();
                    check.add(p, qty);
                    std::cout << "Добавить ещё? (y/n): ";
                    std::string again;
                    std::getline(std::cin, again);
                    if (again != "y") break;
                } catch (...) {
                    std::cerr << "Ошибка: товар не найден\n";
                }
            }

            std::cout << "Способ оплаты (cash/card): ";
            std::string pay;
            std::getline(std::cin, pay);
            double paid = 0;
            if (pay == "cash") {
                std::cout << "Внесено: ";
                std::cin >> paid;
                std::cin.ignore();
            }
            check.print(pay, paid);
            if (pay == "cash") shift.addCash(check.total());
            else shift.addCard(check.total());
        } else if (cmd == "2") {
            shift.printSummary();
            break;
        }
    }

    return 0;
}
