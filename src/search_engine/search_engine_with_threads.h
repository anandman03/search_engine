#include "search_engine.h"

namespace search_engine {

class SearchEngineWithThreads : public SearchEngine {
private:
    void load_dataset() noexcept override;

public:
    SearchEngineWithThreads();
    ~SearchEngineWithThreads();

    bool query_string(const std::string& query_str);
};

};