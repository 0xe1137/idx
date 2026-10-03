//
// Created by elliot on 10/2/26.
//

#ifndef INDEX_FILESCANNER_H
#define INDEX_FILESCANNER_H

#include "../Index/SystemIndex.h"
#include "../File/FileFlags.h"

class FileScanner {
private:
    SystemIndex& index;

    void scanDirectory(const std::string& path, RecordId parent_id);

public:
    explicit FileScanner(SystemIndex& index);

    void start(const std::string& root_path);
};


#endif //INDEX_FILESCANNER_H
