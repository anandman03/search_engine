cmake_minimum_required(VERSION 3.27.6)
project(SEARCH_ENGINE)

set (CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

ADD_LIBRARY(SRC
    src/algorithm/url_ranking.cpp
    src/analytics/measure_time.cpp
    src/analytics/file_processing.cpp
    src/data_structure/node.cpp
    src/data_structure/trie.cpp
    src/file_reader/file_reader.cpp
    src/global_store/cache.cpp
    src/logger/logger.cpp
    src/search_engine/search_engine.cpp
)
target_link_libraries(${PROJECT_NAME} SRC)