#include "url_ranking.h"

namespace algorithm {

UrlRanking::UrlRanking() {
    m_global_cache = global_store::Cache::get_instance();
    refresh();
}

UrlRanking* UrlRanking::get_instance() {
    if (!m_ranking) {
        m_ranking = new UrlRanking();
    }

    return m_ranking;
}

void UrlRanking::set_token_weight(const long double& token_weight) noexcept {
    m_token_weight = token_weight;
}

void UrlRanking::update_partials(const long double& score) noexcept {
    m_partial_score += score;
}

void UrlRanking::compute_ranks(const std::string& token, const std::vector<std::filesystem::path>& file_paths) noexcept {
    for (const auto& file_path : file_paths) {
        auto file_index = m_global_cache->get_file_index(file_path);
        m_effect_grid[file_index][m_global_cache->get_token_index(token)]++;
        m_effect_grid[file_index][m_grid_cols - 1]++;
    }
}

std::string UrlRanking::finalize_ranks() noexcept {
    data_structure::Heap ranking_result;

    for (int r_index = 0 ; r_index < m_grid_rows ; ++r_index) {
        if (!m_effect_grid[r_index][m_grid_cols - 1]) {
            continue;
        }

        long double score = 0;
        uint32_t complete_occurence = INT_MAX;
        for (int c_index = 0 ; c_index < m_grid_cols - 1 ; ++c_index) {
            if (m_effect_grid[r_index][c_index]) {
                complete_occurence = std::min(complete_occurence, m_effect_grid[r_index][c_index]);
            }
            score += (m_token_weight * m_effect_grid[r_index][c_index]);
        }

        if (score) {
            score += (complete_occurence * score);
            ranking_result.add_element(score, m_global_cache->get_file_name(r_index));
        }
    }

    return ranking_result.to_string();
}

void UrlRanking::refresh() noexcept {
    m_partial_score = m_token_weight = 0.0;
    m_grid_rows = m_global_cache->get_file_count();
    m_grid_cols = m_global_cache->get_token_count() + 1;
    m_effect_grid.resize(m_grid_rows, std::vector<uint32_t>(m_grid_cols, 0));

    logger::LOG_DEBUG(std::string("rows: " + std::to_string(m_grid_rows)));
    logger::LOG_DEBUG(std::string("cols: " + std::to_string(m_grid_cols)));
}

};