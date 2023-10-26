#include "search_engine.h"

namespace search_engine {

SearchEngine::SearchEngine() : m_trie(), m_file_reader() {
    for (const auto& file_path : m_file_reader.get_file_paths()) {
        auto tokens = m_file_reader.get_tokens_from_file(file_path);
        for (const auto& token : tokens) {
            m_trie.insert_word(token);
        }
    }
}

bool SearchEngine::query_string(const std::string& query_str) const {
    return m_trie.search_word(query_str);
}

};