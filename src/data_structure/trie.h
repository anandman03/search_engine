#pragma once

#include "node.h"

#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

namespace data_structure {

class Trie {
public:
    Trie();
    ~Trie() = default;

    void insert_word(const std::string& word, const std::filesystem::path& file_path);
    std::tuple<bool, std::vector<std::filesystem::path>> search_word(const std::string& word) const;

private:
    Node* m_root;

    inline static std::mutex WRITE_LOCK;
};

};