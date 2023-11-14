#include "url_ranking.h"

namespace algorithm {

UrlRanking::UrlRanking() {
    m_global_cache = global_store::Cache::get_instance();
    m_effect_grid.resize(m_global_cache->get_file_count(), std::vector<uint32_t>(m_global_cache->get_token_count() + 1, 0));
}

std::string UrlRanking::to_string() noexcept {
    return "";
}

void UrlRanking::compute_ranks(const std::string& token, const std::filesystem::path& file_path) noexcept {
    auto file_index = m_global_cache->get_file_index(file_path);
    m_effect_grid[file_index][m_global_cache->get_token_index(token)]++;
    m_effect_grid[file_index][m_global_cache->get_token_count()]++;
}

std::string UrlRanking::finalize_ranks() noexcept {
    for (int r_index = 0 ; r_index < m_effect_grid.size() ; ++r_index) {
        if (m_effect_grid[r_index][m_effect_grid[r_index].size()-1] == 0) {
            continue;
        }

        uint64_t score = 0;
        uint32_t complete_occurence = INT_MAX;
        for (int c_index = 0 ; c_index < m_effect_grid[r_index].size()-1 ; ++c_index) {
            if (!m_effect_grid[r_index][c_index]) {
                continue;
            }
            complete_occurence = std::min(complete_occurence, m_effect_grid[r_index][c_index]);
            score += (m_token_weight * m_effect_grid[r_index][c_index]);
        }

        if (score) {
            auto file_name = m_global_cache->get_file_name(r_index);
            m_ranking_result[file_name] = score + (complete_occurence * score);
        }
    }

    for (const auto& x : m_ranking_result) {
        std::cout << x.first << ' ' << x.second << '\n';
    }
    
    return "";
}

};