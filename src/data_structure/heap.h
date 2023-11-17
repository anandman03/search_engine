#pragma once

#include <queue>
#include <string>
#include <tuple>
#include <vector>
#include <sstream>

namespace data_structure {

class HeapElement {
private:
    long double m_value;
    std::string m_file_name;

public:
    HeapElement(const long double& value, const std::string& file_name); 
    ~HeapElement() = default;

    const bool operator < (const HeapElement& h_element) const {
        return this->m_value < h_element.m_value;
    }

    std::tuple<long double, std::string> get_node() const;
};

class Heap {
private:
    std::priority_queue<HeapElement> m_queue;

public:
    Heap() = default;
    ~Heap() = default;

    std::string to_string() noexcept;

    void add_element(const long double& value, const std::string& file_name) noexcept;
};

}