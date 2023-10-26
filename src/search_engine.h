#include "trie.h"
#include "file_reader.h"

namespace search_engine {

class SearchEngine {
private:
    data_structure::Trie m_trie;
    file_reader::FileReader m_file_reader;

public:
    SearchEngine();
    ~SearchEngine() = default;

    bool query_string(const std::string& query_str) const;
};

};