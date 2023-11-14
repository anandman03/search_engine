#include "file_reader.h"

#include <iostream>

namespace file_reader {

FileReader::FileReader() : m_folder_path(std::filesystem::current_path()) {
    m_global_cache = global_store::Cache::get_instance();
}

std::vector<std::filesystem::path> FileReader::get_files(std::string dir_path) const {
    auto curr_path = m_folder_path / std::filesystem::path(dir_path);

    for (const auto& entry : std::filesystem::directory_iterator(curr_path)) {
        if (std::filesystem::is_directory(entry)) {
            continue;
        }
        m_global_cache->add_file(entry);
    }

    return m_global_cache->get_file_paths();
}

std::vector<std::string> FileReader::get_tokens_from_file(const std::filesystem::path& file_path) {
    std::error_code err_code;
    if (std::filesystem::is_directory(file_path, err_code)) {
        logger::LOG_ERROR("given path is a directory [" + file_path.string() + "]");
        return {};
    }
    
    std::fstream file_ob;
    file_ob.open(file_path, std::ios::in);

    if (!file_ob.is_open()) {
        logger::LOG_ERROR("cannot open file [" + file_path.string() + "]");
        return {};
    }
    logger::LOG_DEBUG("processing file [" + file_path.string() + "]");

    analytics::FileProcessingStats::inc_files_processed(std::filesystem::file_size(file_path));

    std::string line;
    std::vector<std::string> tokens;
    while (file_ob >> line) {
        tokens.push_back(lower_char(line));
        analytics::FileProcessingStats::inc_words_processed(line);
    }
    file_ob.close();

    return tokens;
}

std::string FileReader::lower_char(std::string line) noexcept {
    for (int index = 0 ; index < line.size() ; ++index) {
        line[index] = std::isalpha(line[index]) ? std::tolower(line[index]) : line[index];
    }
    return line;
}

};