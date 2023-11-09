#pragma once

#include "../global_store/cache.h"
#include "../logger/logger.h"

#include <algorithm>
#include <filesystem>
#include <map>
#include <string>
#include <unordered_map>

namespace algorithm {

class UrlRanking {
private:
    uint64_t m_token_weight;
    std::vector<std::vector<uint32_t>> m_effect_grid;
    std::unordered_map<std::filesystem::path, uint64_t> m_ranking_result;

    global_store::Cache* m_global_cache;

    std::string to_string() noexcept;

public:
    UrlRanking();
    ~UrlRanking() = default;

    void compute_ranks(const std::string& token, const std::filesystem::path& file_path) noexcept;
    std::string finalize_ranks() noexcept;
};

};