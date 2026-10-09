#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>

struct WordStat {
    std::string word;
    std::size_t count;
};

class WordCounter {
public:
    void readFile(const std::string& filename);
    void printReport() const;

private:
    std::unordered_map<std::string, std::size_t> word_counts;
    std::size_t total_words = 0;
    std::vector<WordStat> SortStats() const;
};
