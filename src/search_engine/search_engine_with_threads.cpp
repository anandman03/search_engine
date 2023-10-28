#include "search_engine_with_threads.h"

namespace search_engine {

SearchEngineWithThreads::SearchEngineWithThreads() : SearchEngine() {}

void SearchEngineWithThreads::load_dataset() noexcept {
    return;
}

bool SearchEngineWithThreads::query_string(const std::string& query_str) {
    return true;
}

};