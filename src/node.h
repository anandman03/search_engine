#include <vector>

namespace search_engine {

class Node {
private:
    char m_value;
    bool m_is_end;
    std::vector<Node*> m_branches;

public:
    Node();
    ~Node() = default;

    /* getters */
    char get_value() const;
    bool check_end() const;

    /* setters */
    void mark_end();

    /* methods */
    void create_branch(const char& query_char);
    Node* change_branch(const char& query_char);
    bool check_if_branch_exists(const char& query_char) const;
};

};