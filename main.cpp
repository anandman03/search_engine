#include "src/search_engine/search_engine.h"

#include <iostream>

int main()
{
    int threads = 2;
    search_engine::SearchEngine search(threads);

    std::cout << analytics::FileProcessingStats::generate_stats() << std::endl;

    search.query_string("orphaned");
    search.query_string("orphaned's  child");
    search.query_string("Westminster Dog Show");

    return 0;
}