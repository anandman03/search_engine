#include "trie.h"

#include <iostream>

namespace data_structure {

Trie::Trie() : m_root(new Node()), m_score(0), m_query_str() {
    m_ranking_algo = algorithm::UrlRanking::get_instance();
}

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

void Trie::search_word(const std::string& word) {
    m_score = 1;
    m_query_str = word;
    Node* curr_node = m_root;

    size_t count = 0;
    for (auto& curr_char : word) {
        if (!curr_node->check_if_branch_exists(curr_char)) {
            m_score = (double) count / word.size();
            break;
        }

        ++count;
        curr_node = curr_node->change_branch(curr_char);
    }
    recursive_search(curr_node);
}

void Trie::recursive_search(Node* curr_node) const {
    if (!curr_node) {
        return;
    }

    if (curr_node->check_end()) {
        if (m_score == 1.0) {
            m_ranking_algo->compute_ranks(m_query_str, curr_node->get_files_included());
        }
        else m_ranking_algo->update_partials(m_score);
    }

    if (curr_node->get_branches().empty()) {
        return;
    }

    for (const auto& branch : curr_node->get_branches()) {
        recursive_search(branch.second);
    }
}

};