#pragma once

#include "../analytics/file_processing.h"
#include "../global_store/cache.h"
#include "../logger/logger.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace file_reader {

class FileReader {
private:
    global_store::Cache* m_global_cache;
    std::filesystem::path m_folder_path;

    std::string lower_char(std::string line) noexcept;

public:
    FileReader();
    ~FileReader() = default;

    std::vector<std::filesystem::path> get_files(std::string dir_path = "") const;
    std::vector<std::string> get_tokens_from_file(const std::filesystem::path& file_path);
};

};