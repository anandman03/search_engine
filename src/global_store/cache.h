#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace global_store {

class Cache {
private:
    inline static Cache* m_instance = nullptr;

    size_t m_token_count = 0;
    std::unordered_map<std::string, size_t> m_token_list;
    std::unordered_map<std::string, size_t> m_file_to_index_mapping;

    std::vector<std::filesystem::path> m_files;

    Cache() = default;

public:
    static Cache* get_instance() noexcept;

    size_t get_file_count() noexcept;
    size_t get_token_count() noexcept;

    void add_file(const std::filesystem::path& file_path) noexcept;
    size_t get_file_index(const std::filesystem::path& file_path) noexcept;
    std::string get_file_name(const size_t& file_index) noexcept;

    void add_token(const std::string& token) noexcept;
    size_t get_token_index(const std::string& token) noexcept;
};

};