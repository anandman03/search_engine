cmake_minimum_required(VERSION 3.27.6)
project(SEARCH_ENGINE)

set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

ADD_LIBRARY(SRC
    src/node.cpp
    src/trie.cpp
    src/file_reader.cpp
    src/search_engine.cpp
)
target_link_libraries(${PROJECT_NAME} SRC)