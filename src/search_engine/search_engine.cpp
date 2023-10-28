#include "search_engine.h"

namespace search_engine {

SearchEngine::SearchEngine() : m_trie(), m_file_reader() {
    RECORD_START_TIME; load_stopwords();
    load_dataset(); RECORD_ELAPSED_TIME;
}

void SearchEngine::load_dataset() noexcept {
    for (const auto& file_path : m_file_reader.get_files(SearchEngine::DATASET_PATH)) {
        auto tokens = m_file_reader.get_tokens_from_file(file_path);
        for (const auto& token : tokens) {
            m_trie.insert_word(token);
        }
    }
}

void SearchEngine::load_stopwords() noexcept {
    for (const auto& file_path : m_file_reader.get_files(SearchEngine::STOPWORDS_PATH)) {
        auto tokens = m_file_reader.get_tokens_from_file(file_path);
        for (const auto& token : tokens) {
            m_stopwords.insert(token);
        }
    }
}

bool SearchEngine::query_string(const std::string& query_str) {
    RECORD_START_TIME; auto res = m_trie.search_word(query_str); RECORD_ELAPSED_TIME;

    return res;
}

};