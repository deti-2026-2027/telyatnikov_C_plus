#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <cctype>

struct WordStat {
    std::string word;
    std::size_t count;
};

class WordCounter {
public:
    void readFile(const std::string& filename) {
        std::ifstream file(filename);

        std::string word;
        while (file >> word) {
            for (char& c : word) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

            word_counts[word]++;
            total_words++;
        }
    }

    void printReport(std::ostream& out = std::cout) {
        if (total_words == 0) {
            out << "нет слов\n";
            return;
        }

        std::vector<WordStat> stats = SortStats();

        out << std::fixed << std::setprecision(2);

        for (const auto& item : stats) {
            double procent = (static_cast<double>(item.count) / total_words) * 100.0;
            out << item.word << " " << item.count << " " << procent << "%\n";
        }
    }

private:
    std::unordered_map<std::string, std::size_t> word_counts;
    std::size_t total_words = 0;

    std::vector<WordStat> SortStats() const {
        std::vector<WordStat> stats;
        stats.reserve(word_counts.size());

        for (const auto& [word, count] : word_counts) {
            stats.push_back({word, count});
        }

        std::sort(stats.begin(), stats.end(), [](const WordStat& a, const WordStat& b) {
            if (a.count != b.count) return a.count > b.count;
            else return a.word < b.word;
        });

        return stats;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "путь файла напиши, дурень\n";
        return 1;
    }

    WordCounter counter;
    counter.readFile(argv[1]);
    counter.printReport();
    return 0;
}
