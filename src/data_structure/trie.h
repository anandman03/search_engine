#pragma once

#include "node.h"

#include <memory>
#include <mutex>
#include <string>

namespace data_structure {

class Trie {
public:
    Trie();
    ~Trie() = default;

    void insert_word(const std::string& word);
    bool search_word(const std::string& word) const;

private:
    Node* m_root;

    inline static std::mutex WRITE_LOCK;
};

};