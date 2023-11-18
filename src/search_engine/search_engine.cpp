#include "search_engine.h"

namespace search_engine {

SearchEngine::SearchEngine(const int& threads) : m_trie(), m_file_reader(), m_threads(threads) {
    RECORD_START_TIME; 
    m_global_cache = global_store::Cache::get_instance();
    m_ranking_algo = algorithm::UrlRanking::get_instance();
    load_stopwords(); load_dataset(); 
    RECORD_ELAPSED_TIME;
}

void SearchEngine::load_dataset() noexcept {
    std::vector<std::filesystem::path> files = m_file_reader.get_files(SearchEngine::DATASET_PATH);
    const int& file_list_size = files.size();
    if (!file_list_size) {
        logger::LOG_ERROR("No data file present at path[" + DATASET_PATH + "]");
        return;
    }
    
    std::function<void(int,int)> process_files = [&] (const int& start_idx, const int& end_idx) {
        for (int index = start_idx ; index < end_idx ; ++index) {
            for (const auto& token : m_file_reader.get_tokens_from_file(files[index])) {
                m_trie.insert_word(token, files[index]);
            }
        }
    };

    int base_index = 0;
    std::vector<std::thread> workers;
    const int chunk_size = file_list_size / m_threads;
    const int rem_chunk_size = file_list_size - (chunk_size * m_threads);

    while (base_index + chunk_size <= file_list_size) {
        workers.emplace_back(std::thread(process_files, base_index, base_index + chunk_size));
        base_index += chunk_size;
    }
    if (rem_chunk_size) {
        workers.emplace_back(std::thread(process_files, base_index, files.size()));
    }

    for (auto&& worker : workers) {
        worker.join();
    }
}

void SearchEngine::load_stopwords() noexcept {
    auto stopword_file = m_file_reader.get_files(SearchEngine::STOPWORDS_PATH);
    if (stopword_file.empty()) {
        return;
    }
    auto tokens = m_file_reader.get_tokens_from_file(stopword_file[0]);

    for (const auto& token : tokens) {
        m_stopwords.insert(token);
    }
}

std::vector<std::string> SearchEngine::filter_stopwords(const std::string& query_str) noexcept {
    std::string curr_str;
    std::vector<std::string> refined_query;
    
    std::function<bool(std::string)> is_query_token_valid = [&] (const std::string& str) {
        return (!curr_str.empty() && !m_stopwords.count(curr_str));
    };
    
    for (const char& curr_char : query_str) {
        if (curr_char == ' ') {
            if (is_query_token_valid(curr_str)) {
                m_global_cache->add_token(curr_str);
                refined_query.emplace_back(curr_str);
            }
            curr_str.clear();
        }
        else {
            curr_str += std::tolower(curr_char);
        }
    }
    if (is_query_token_valid(curr_str)) {
        m_global_cache->add_token(curr_str);
        refined_query.emplace_back(curr_str);
    }

    return refined_query;
}

void SearchEngine::query_string(const std::string& query_str) {
    RECORD_START_TIME;
    
    m_global_cache->clear_tokens();
    auto filtered_query = filter_stopwords(query_str);

    m_ranking_algo->refresh();
    m_ranking_algo->set_token_weight(1.0L / (long double) filtered_query.size());

    for (const auto& token : filtered_query) {
        m_trie.search_word(token);
    }
    logger::LOG_INFO(m_ranking_algo->finalize_ranks());

    RECORD_ELAPSED_TIME;
}

};