#include "node.h"

namespace data_structure {

Node::Node() : m_value('$'), m_is_end(false), m_branches() {}

Node::Node(const char& value) : m_value(value), m_is_end(false), m_branches() {}

char Node::get_value() const {
    return m_value;
}

bool Node::check_end() const {
    return m_is_end;
}

void Node::mark_end() {
    m_is_end = true;
}

void Node::create_branch(const char& query_char) {
    m_branches[query_char] = new Node(query_char);
}

Node* Node::change_branch(const char& query_char) {
    if (!check_if_branch_exists(query_char)) {
        return nullptr;
    }

    return m_branches[query_char];
}

bool Node::check_if_branch_exists(const char& query_char) const {
    return m_branches.count(query_char) == 1;
}

};