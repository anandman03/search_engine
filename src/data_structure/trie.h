#pragma once

#include "node.h"
#include "../algorithm/url_ranking.h"

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

    algorithm::UrlRanking* m_ranking_algo;

    void insert_word(const std::string& word, const std::filesystem::path& file_path);
    void search_word(const std::string& word);
    void recursive_search(Node* curr_node) const;

private:
    Node* m_root;
    long double m_score;
    std::string m_query_str;

    inline static std::mutex WRITE_LOCK;
};

};