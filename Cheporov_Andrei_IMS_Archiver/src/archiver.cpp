
#include "archiver.hpp"
#include "signal_handler.hpp"
#include <fstream>
#include <zlib.h>
#include <stdexcept>

void archive_file(const std::string& input_path, const std::string& output_path) {
    std::ifstream in(input_path, std::ios::binary);
    gzFile out = gzopen(output_path.c_str(), "wb");
    if (!in || !out) throw std::runtime_error("Ошибка открытия файлов");

    char buffer[8192];
    while (in && !is_interrupted()) {
        in.read(buffer, sizeof(buffer));
        std::streamsize bytes_read = in.gcount();
        if (bytes_read > 0) gzwrite(out, buffer, static_cast<unsigned>(bytes_read));
    }

    gzclose(out);
    in.close();
}
