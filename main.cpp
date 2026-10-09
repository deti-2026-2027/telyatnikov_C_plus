#include "WordCounter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "не указан путь к файлу\n";
        return 1;
    }

    WordCounter counter;
    counter.readFile(argv[1]);
    counter.printReport();

    return 0;
}
