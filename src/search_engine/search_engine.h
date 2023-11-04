#pragma once

#include "../analytics/file_processing.h"
#include "../analytics/measure_time.h"
#include "../data_structure/trie.h"
#include "../file_reader/file_reader.h"
#include "../logger/logger.h"

#include <mutex>
#include <thread>
#include <sstream>
#include <unordered_set>

// TODO: add exact string matching like "exact words"
// TODO: substring matching
// TODO: result ranking algorithm
// TODO: cache previous queries

namespace search_engine {

class SearchEngine {
protected:
    int m_threads;
    data_structure::Trie m_trie;
    file_reader::FileReader m_file_reader;
    std::unordered_set<std::string> m_stopwords;

    inline static std::mutex WRITE_LOCK;
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

    bool query_string(const std::string& query_str);
};

};