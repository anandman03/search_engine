#include "trie.h"

#include <iostream>

namespace data_structure {

Trie::Trie() : m_root(new Node()) {}

void Trie::insert_word(const std::string& word) {
    Node* curr_node = m_root;

    for (auto curr_char : word) {
        curr_char = tolower(curr_char);
        if (!curr_node->check_if_branch_exists(curr_char)) {
            curr_node->create_branch(curr_char);
        }

        curr_node = curr_node->change_branch(curr_char);
    }

    curr_node->mark_end();

    return;
}

bool Trie::search_word(const std::string& word) const {
    Node* curr_node = m_root;

    for (auto& curr_char : word) {
        if (!curr_node->check_if_branch_exists(curr_char)) {
            return false;
        }

        curr_node = curr_node->change_branch(curr_char);
    }

    return (curr_node->check_end());
}

};