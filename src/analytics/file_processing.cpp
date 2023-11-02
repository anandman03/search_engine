#include "file_processing.h"

namespace analytics {

void FileProcessingStats::inc_words_processed(const std::string& word) noexcept {
    std::lock_guard<std::mutex> update_guard(FileProcessingStats::STAT_MUTEX);
    ++TOTAL_WORDS_PROCESSED;
}

void FileProcessingStats::inc_files_processed(const uint64_t& file_size) noexcept {
    std::lock_guard<std::mutex> update_guard(FileProcessingStats::STAT_MUTEX);
    TOTAL_FILES_PROCESSED += file_size;
}

uint64_t FileProcessingStats::get_files_processed() noexcept {
    return TOTAL_FILES_PROCESSED;
}

uint64_t FileProcessingStats::get_words_processed() noexcept {
    return TOTAL_WORDS_PROCESSED;
}

std::string FileProcessingStats::generate_stats() noexcept {
    std::stringstream ss;
    ss << "Total files processed: " << TOTAL_FILES_PROCESSED << " bytes" << '\n';
    ss << "Total words processed: " << TOTAL_WORDS_PROCESSED << '\n';
    ss << "Longest word processed: " << LONGEST_WORD_PROCESSED << '\n';
    return ss.str();
}

}