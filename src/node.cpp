#include "node.h"

namespace search_engine {

Node::Node() : m_value('$'), m_is_end(false), m_branches(std::vector<Node*>(26, nullptr)) {}

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
    m_branches[query_char - 'a'] = new Node();
}

Node* Node::change_branch(const char& query_char) {
    return m_branches[query_char - 'a'];
}

bool Node::check_if_branch_exists(const char& query_char) const {
    return m_branches[query_char - 'a'] != nullptr;
}

};