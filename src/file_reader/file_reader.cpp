#include "file_reader.h"

#include <iostream>

namespace file_reader {

FileReader::FileReader() : m_folder_path(std::filesystem::current_path()) {}

std::vector<std::filesystem::path> FileReader::get_files(std::string dir_path) const {
    std::vector<std::filesystem::path> result;
    auto curr_path = m_folder_path / std::filesystem::path(dir_path);

    for (const auto& entry : std::filesystem::directory_iterator(curr_path)) {
        result.emplace_back(entry.path());
    }

    return result;
}

std::vector<std::string> FileReader::get_tokens_from_file(const std::filesystem::path& file_path) const {
    std::error_code err_code;
    if (std::filesystem::is_directory(file_path, err_code)) {
        return {};
    }
    
    std::fstream file_ob;
    file_ob.open(file_path, std::ios::in);

    if (!file_ob.is_open()) {
        std::cout << "[ERROR]: cannot open file: " << file_path << std::endl;
    }

    std::cout << "[DEBUG]: processing file: " << file_path << std::endl;

    std::string line;
    std::vector<std::string> tokens;
    while (file_ob >> line) {
        tokens.push_back(line);
    }
    file_ob.close();

    return tokens;
}

};