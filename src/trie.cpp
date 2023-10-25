#include "trie.h"

#include <iostream>

namespace search_engine {

Trie::Trie() : m_root(new Node()) {}

void Trie::insert(const std::string& word) {
    Node* curr_node = m_root;

    for (const auto& curr_char : word) {
        if (!curr_node->check_if_branch_exists(curr_char)) {
            curr_node->create_branch(curr_char);
        }

        curr_node = curr_node->change_branch(curr_char);
    }

    curr_node->mark_end();
    std::cout << "[DEBUG]: added word " << word << std::endl;

    return;
}

};