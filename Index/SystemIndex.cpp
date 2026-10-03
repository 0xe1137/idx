//
// Created by elliot on 10/2/26.
//

#include "SystemIndex.h"

SystemIndex::SystemIndex() {
    records.reserve(1'000'000);
    string_arena.reserve(64 * 1024 * 1024);

    string_arena.push_back('\0'); // offset 0 == empty string

    records.push_back(FileRecord{
        .id = ROOT_ID,
        .parent_id = INVALID_ID,
        .name_offset = 0,
        .flags = FileFlags::Dir,
    });
}

std::uint64_t SystemIndex::internString(std::string_view name) {
    const auto offset = static_cast<std::uint64_t>(string_arena.size());
    string_arena.insert(string_arena.end(), name.begin(), name.end());
    string_arena.push_back('\0');
    return offset;
}

RecordId SystemIndex::addRecord(std::string_view name, std::string_view full_path, RecordId parent, FileFlags flags) {
    const RecordId id = records.size();
    records.push_back(FileRecord{
        .id = id,
        .parent_id = parent,
        .name_offset = internString(name),
        .flags = flags,
    });
    return id;
}

void SystemIndex::setRootName(std::string_view name) {
    records[ROOT_ID].name_offset = internString(name);
}

std::string_view SystemIndex::getName(RecordId id) const {
    return std::string_view{string_arena.data() + records[id].name_offset };
}

std::string SystemIndex::buildPath(RecordId id) const {
    std::vector<std::string_view> parts;
    for (RecordId cur = 0; cur != INVALID_ID; cur = records[cur].parent_id) {
        parts.push_back(getName(cur));
    }

    std::string path;
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
        if (!path.empty() && path.back() != '/') path += '/';
        path += *it;
    }
    return path;
}
