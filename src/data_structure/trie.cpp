#include "trie.h"

#include <iostream>

namespace data_structure {

Trie::Trie() : m_root(new Node()) {}

void Trie::insert_word(const std::string& word, const std::filesystem::path& file_path) {
    std::lock_guard<std::mutex> data_structure_guard(WRITE_LOCK);

    Node* curr_node = m_root;
    for (auto curr_char : word) {
        curr_char = tolower(curr_char);
        if (!curr_node->check_if_branch_exists(curr_char)) {
            curr_node->create_branch(curr_char);
        }

        curr_node = curr_node->change_branch(curr_char);
    }

    curr_node->mark_end();
    curr_node->add_included_file(file_path);

    return;
}

std::tuple<bool, std::vector<std::filesystem::path>> Trie::search_word(const std::string& word) const {
    Node* curr_node = m_root;

    for (auto& curr_char : word) {
        if (!curr_node->check_if_branch_exists(curr_char)) {
            return std::tuple(false, std::vector<std::filesystem::path>());
        }

        curr_node = curr_node->change_branch(curr_char);
    }

    return std::tuple(curr_node->check_end(), curr_node->get_files_included());
}

};