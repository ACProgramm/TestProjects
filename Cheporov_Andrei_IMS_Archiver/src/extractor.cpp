
#include "extractor.hpp"
#include "signal_handler.hpp"
#include <fstream>
#include <zlib.h>
#include <stdexcept>

void extract_file(const std::string& input_path, const std::string& output_path) {
    gzFile in = gzopen(input_path.c_str(), "rb");
    std::ofstream out(output_path, std::ios::binary);
    if (!in || !out) throw std::runtime_error("Ошибка открытия файлов");

    char buffer[8192];
    int bytes;
    while ((bytes = gzread(in, buffer, sizeof(buffer))) > 0 && !is_interrupted()) {
        out.write(buffer, bytes);
    }

    gzclose(in);
    out.close();
}
