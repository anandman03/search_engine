#include "src/search_engine/search_engine.h"

#include <iostream>

int main()
{
    int threads = 2;
    search_engine::SearchEngine search(threads);

    std::cout << analytics::FileProcessingStats::generate_stats() << std::endl;

    std::cout << search.query_string("orphaned") << std::endl;

    return 0;
}