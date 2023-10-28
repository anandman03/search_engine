#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace file_reader {

class FileReader {
private:
    std::filesystem::path m_folder_path;

public:
    FileReader();
    ~FileReader() = default;

    std::vector<std::filesystem::path> get_files(std::string dir_path = "") const;
    std::vector<std::string> get_tokens_from_file(const std::filesystem::path& file_path) const;
};

};