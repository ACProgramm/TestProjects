
#include "include/archiver.hpp"
#include "include/extractor.hpp"
#include "include/signal_handler.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Использование: myapp a|e <входной файл> <выходной файл>\n";
        return 1;
    }

    setup_signal_handler();

    try {
        std::string mode = argv[1];
        std::string input = argv[2];
        std::string output = argv[3];

        if (mode == "a") {
            archive_file(input, output);
            std::cout << "Файл заархивирован.\n";
        } else if (mode == "e") {
            extract_file(input, output);
            std::cout << "Файл распакован.\n";
        } else {
            std::cerr << "Неверная команда: используйте 'a' для архивации или 'e' для извлечения.\n";
            return 1;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
