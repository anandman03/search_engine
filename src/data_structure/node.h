#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

namespace data_structure {

class Node {
private:
    char m_value;
    bool m_is_end;
    std::unordered_map<char, Node*> m_branches;
    std::vector<std::filesystem::path> m_files_included;

public:
    Node();
    Node(const char& value);

    ~Node() = default;

    /* getters */
    char get_value() const;
    bool check_end() const;
    std::unordered_map<char, Node*> get_branches() const;
    std::vector<std::filesystem::path> get_files_included() const;

    /* setters */
    void mark_end();
    void add_included_file(const std::filesystem::path& file_path);

    /* methods */
    void create_branch(const char& query_char);
    Node* change_branch(const char& query_char);
    bool check_if_branch_exists(const char& query_char) const;
};

};