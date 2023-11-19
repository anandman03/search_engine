#pragma once

#include <cstdint>
#include <algorithm>
#include <mutex>
#include <string>
#include <sstream>

namespace analytics {

class FileProcessingStats {
private:
    inline static std::mutex STAT_MUTEX;

    inline static uint64_t TOTAL_WORDS_PROCESSED = 0;
    inline static uint64_t TOTAL_FILES_PROCESSED = 0;
    inline static uint32_t LONGEST_WORD_PROCESSED = 0;

    FileProcessingStats() = default;
    FileProcessingStats(const FileProcessingStats&) = delete;

    void operator = (const FileProcessingStats&) = delete;

public:
    ~FileProcessingStats() = default;

    static void inc_words_processed(const std::string& word) noexcept;
    static void inc_files_processed(const uint64_t& file_size) noexcept;

    static uint64_t get_words_processed() noexcept;
    static uint64_t get_files_processed() noexcept;

    static std::string generate_stats() noexcept;
};

}