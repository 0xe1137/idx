//
// Created by elliot on 10/2/26.
//

#include "FileScanner.h"

#include <algorithm>
#include <dirent.h>
#include <array>
#include <string>
#include <string_view>

static bool shouldIgnore(const std::string& path) {
    static constexpr std::array ignoredPatterns {
        std::string_view{"Library/Mobile Documents"},
        std::string_view{"Library/CloudStorage"},
        std::string_view{".Trash"},
        std::string_view{".Spotlight-V100"},
        std::string_view{"/.git"},
        std::string_view{"/node_modules"},
        std::string_view{"/.rvm"},
        std::string_view{"/.vscode/extensions"},
        std::string_view{"/.rustup"},
        std::string_view{"/.cargo/registry"},
    };

    return std::ranges::any_of(ignoredPatterns, [&](std::string_view pattern) {
        return path.find(pattern) != std::string::npos;
    });
}

FileScanner::FileScanner(SystemIndex &index_ref)
    : index{index_ref} {}

void FileScanner::start(const std::string &root_path) {
    index.setRootName(root_path);
    scanDirectory(root_path, ROOT_ID);
}

void FileScanner::scanDirectory(const std::string &path, RecordId parent_id) {
    if (shouldIgnore(path)) return;

    DIR* dir = ::opendir(path.c_str());
    if (!dir) return;

    struct dirent* entry;

    while ((entry = ::readdir(dir)) != nullptr) {
        std::string_view name(entry->d_name);

        if (name == "." || name == "..") continue;
        auto flags = FileFlags::None;

        if (!name.empty() && name[0] == '.') {
            flags |= FileFlags::Hidden;
        }

        std::string full_path;
        full_path.reserve(path.size() + 1 + name.size());

        full_path += path;
        full_path += '/';
        full_path += name;

        if (entry->d_type == DT_DIR) {
            flags |= FileFlags::Dir;

            const RecordId id = index.addRecord(
                name,
                full_path,
                parent_id,
                flags);
            scanDirectory(full_path, id);
        } else if (entry->d_type == DT_REG) {
            flags |= FileFlags::File;

            index.addRecord(name, full_path, parent_id, flags);
        } else if (entry->d_type == DT_LNK) {
            flags |= FileFlags::Symlink;

            index.addRecord(name, full_path, parent_id, flags);
        }
    }

    ::closedir(dir);
}
