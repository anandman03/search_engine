#include "cache.h"

namespace global_store {

Cache* Cache::get_instance() noexcept {
    if (m_instance != nullptr) {
        return m_instance;
    }
    return m_instance = new Cache();
}

size_t Cache::get_file_count() noexcept {
    return m_files.size();
}

size_t Cache::get_token_count() noexcept {
    return m_token_count;
}

void Cache::add_file(const std::filesystem::path& file_path) noexcept {
    m_files.emplace_back(file_path);
    m_file_to_index_mapping[file_path.string()] = m_files.size() - 1;
}

size_t Cache::get_file_index(const std::filesystem::path& file_path) noexcept {
    return m_file_to_index_mapping.count(file_path.string()) ? m_file_to_index_mapping[file_path] : SIZE_T_MAX;
}

std::string Cache::get_file_name(const size_t& file_index) noexcept {
    return file_index < m_files.size() ? m_files[file_index].c_str() : "";
}

void Cache::add_token(const std::string& token) noexcept {
    m_token_list[token] = m_token_count++;
}

size_t Cache::get_token_index(const std::string& token) noexcept {
    return m_token_list.count(token) ? m_token_list[token] : SIZE_T_MAX;
}

};