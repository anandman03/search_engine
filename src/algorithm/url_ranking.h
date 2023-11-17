#pragma once

#include "../data_structure/heap.h"
#include "../global_store/cache.h"
#include "../logger/logger.h"

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace algorithm {

class UrlRanking {
private:
    long double m_token_weight;
    size_t m_grid_rows, m_grid_cols;
    std::vector<std::vector<uint32_t>> m_effect_grid;

    global_store::Cache* m_global_cache;

public:
    UrlRanking();
    ~UrlRanking() = default;

    void set_token_weight(const long double& token_weight) noexcept;
    void compute_ranks(const std::string& token, const std::vector<std::filesystem::path>& file_path) noexcept;
    std::string finalize_ranks() noexcept;
};

};