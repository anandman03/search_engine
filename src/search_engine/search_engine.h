#pragma once

#include "../algorithm/url_ranking.h"
#include "../analytics/file_processing.h"
#include "../analytics/measure_time.h"
#include "../data_structure/trie.h"
#include "../file_reader/file_reader.h"
#include "../global_store/cache.h"
#include "../logger/logger.h"

#include <thread>
#include <sstream>
#include <unordered_set>

namespace search_engine {

class SearchEngine {
protected:
    int m_threads;
    data_structure::Trie m_trie;
    file_reader::FileReader m_file_reader;
    global_store::Cache* m_global_cache;
    algorithm::UrlRanking* m_ranking_algo;

    std::unordered_set<std::string> m_stopwords;

    inline static const std::string DATASET_PATH = "data/dataset/";
    inline static const std::string STOPWORDS_PATH = "data/";

    metrics::MeasureTime m_measure_time;
    #define RECORD_START_TIME m_measure_time.start()
    #define RECORD_ELAPSED_TIME m_measure_time.elapsed_time()

    void load_dataset() noexcept;
    void load_stopwords() noexcept;

    std::vector<std::string> filter_stopwords(const std::string& query_str) noexcept;

public:
    SearchEngine(const int& threads);
    ~SearchEngine() = default;

    void query_string(const std::string& query_str);
};

};