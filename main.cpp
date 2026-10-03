#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Index/SystemIndex.h"
#include "Scanner/FileScanner.h"

int main(int argc, char **argv) {
    std::string root;
    if (argc > 1) {
        root = argv[1];
    } else if (const char* home = std::getenv("HOME")) {
        root = home;
    } else {
        std::cerr << "usage: index <root>\n";
        return 1;
    }

    SystemIndex index;
    FileScanner scanner{index};


    const auto t0 = std::chrono::steady_clock::now();
    scanner.start(root);
    const auto t1 = std::chrono::steady_clock::now();

    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "Indexed " << index.getTotalRecords() << " records in " << ms << " ms\n";

    // sanity check: rebuild a few paths from parent links
    for (RecordId id = 1; id < std::min<std::size_t>(11, index.getTotalRecords()); ++id) {
        std::cout << "  " << index.buildPath(id) << '\n';
    }
}