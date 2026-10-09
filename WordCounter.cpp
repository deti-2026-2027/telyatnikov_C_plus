#include "WordCounter.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

void WordCounter::readFile(const std::string& filename) {
    std::ifstream file(filename);

    std::string word;
    while (file >> word) {
        for (char& c : word) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }

        word_counts[word]++;
        total_words++;
    }
}

void WordCounter::printReport() const {
    if (total_words == 0) {
        std::cout << "нет слов\n";
        return;
    }

    std::vector<WordStat> stats = SortStats();

    for (const auto& item : stats) {
        double percent = (static_cast<double>(item.count) / total_words) * 100.0;
        std::cout << item.word << " " << item.count << " " << percent << "%\n";
    }
}

std::vector<WordStat> WordCounter::SortStats() const {
    std::vector<WordStat> stats;
    stats.reserve(word_counts.size());

    for (const auto& [word, count] : word_counts) {
        stats.push_back({word, count});
    }

    std::sort(stats.begin(), stats.end(), [](const WordStat& a, const WordStat& b) {
        if (a.count != b.count) {
            return a.count > b.count;
        }
        return a.word < b.word;
    });

    return stats;
}
