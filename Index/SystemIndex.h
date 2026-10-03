//
// Created by elliot on 10/2/26.
//

#ifndef INDEX_SYSTEMINDEX_H
#define INDEX_SYSTEMINDEX_H

#include <cstddef>
#include <vector>
#include <cstdint>
#include <string_view>
#include <string>

#include "../File/FileRecord.h"

class SystemIndex {
private:
    std::vector<FileRecord> records;
    std::vector<char> string_arena; // null-terminated arena

public:
    SystemIndex();

    std::uint64_t internString(std::string_view name);

    RecordId addRecord(std::string_view name,
        std::string_view full_path,
        RecordId parent,
        FileFlags flags);

    void setRootName(std::string_view name);

    [[nodiscard]] std::string_view getName(RecordId id) const;
    [[nodiscard]] std::string buildPath(RecordId id) const;
    [[nodiscard]] std::size_t getTotalRecords() const { return records.size(); }
};




#endif //INDEX_SYSTEMINDEX_H
