//
// Created by elliot on 10/2/26.
//

#ifndef INDEX_FILEFLAGS_H
#define INDEX_FILEFLAGS_H

#include <cstdint>

/**
 * FileFlags is an enum representing basic file type information.
 */
enum class FileFlags : uint32_t {
    None = 0,
    File = 1 << 0,
    Dir = 1 << 1,
    Symlink = 1 << 2,
    Hidden = 1 << 3,
    Deleted = 1 << 4,
};


// =========== Overloads =============
// ===================================

constexpr FileFlags operator|(const FileFlags lhs, const FileFlags rhs) noexcept {
    return static_cast<FileFlags>(
        static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr FileFlags& operator|=(FileFlags& lhs, const FileFlags rhs) noexcept {
    lhs = lhs | rhs;
    return lhs;
}

/**
 * Check for flag value.
 *
 * @param flags flags to check against
 * @param flag_to_check specific flag value to check
 * @return boolean true if flags has `flag_to_check`, false otherwise.
 */
constexpr bool has_flag(FileFlags flags, FileFlags flag_to_check) noexcept {
    return (static_cast<uint32_t>(flags) & static_cast<uint32_t>(flag_to_check));
}


#endif //INDEX_FILEFLAGS_H
