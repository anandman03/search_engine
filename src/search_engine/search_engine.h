#include "../data_structure/trie.h"
#include "../file_reader/file_reader.h"
#include "../analytics/measure_time.h"

#include <unordered_set>

// TODO: add complex queries
// TODO: add multi-threading to file reading

namespace search_engine {

class SearchEngine {
private:
    data_structure::Trie m_trie;
    file_reader::FileReader m_file_reader;
    std::unordered_set<std::string> m_stopwords;

    inline static const std::string DATASET_PATH = "data/dataset/";
    inline static const std::string STOPWORDS_PATH = "data/";

    metrics::MeasureTime m_measure_time;
    #define RECORD_START_TIME m_measure_time.start()
    #define RECORD_ELAPSED_TIME m_measure_time.elapsed_time()

    void load_dataset() noexcept;
    void load_stopwords() noexcept;

public:
    SearchEngine();
    ~SearchEngine() = default;

    bool query_string(const std::string& query_str);
};

};