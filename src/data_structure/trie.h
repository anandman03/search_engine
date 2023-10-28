#include "node.h"

#include <memory>
#include <string>

namespace data_structure {

class Trie {
public:
    Trie();
    ~Trie() = default;

    void insert_word(const std::string& word);
    bool search_word(const std::string& word) const;

private:
    Node* m_root;
};

};