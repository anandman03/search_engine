#include "src/search_engine.h"

#include <iostream>

int main()
{
    search_engine::SearchEngine search;
    std::cout << search.query_string("himselfs") << std::endl;

    return 0;
}