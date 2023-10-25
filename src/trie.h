#include "node.h"

#include <memory>
#include <string>

namespace search_engine {

class Trie {
public:
    Trie();
    ~Trie() = default;

    void insert(const std::string& word);

private:
    Node* m_root;
};

};