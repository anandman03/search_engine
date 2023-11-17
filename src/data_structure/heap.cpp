#include "heap.h"

namespace data_structure {

HeapElement::HeapElement(const long double& value, const std::string& file_name) : m_value(value), m_file_name(file_name) {}

std::tuple<long double, std::string> HeapElement::get_node() const {
    return std::tuple(m_value, m_file_name);
}

void Heap::add_element(const long double& value, const std::string& file_name) noexcept {
    if (m_queue.size() < 10) {
        m_queue.push(HeapElement(value, file_name));
    }

    auto [node_val, node_file_name] = m_queue.top().get_node();
    if (node_val >= value) {
        return;
    }

    m_queue.pop();
    m_queue.push(HeapElement(value, file_name));
}

std::string Heap::to_string() noexcept {
    std::stringstream ss;
    std::priority_queue<HeapElement> t_queue;
    while (!m_queue.empty()) {
        auto [node_val, node_file_name] = m_queue.top().get_node();

        ss << "File: " << node_file_name << " [" << node_val << "] \n";
        
        t_queue.push(m_queue.top());
        m_queue.pop();
    }

    while (!t_queue.empty()) {
        m_queue.push(t_queue.top());
        t_queue.pop();
    }

    return ss.str();
}

}