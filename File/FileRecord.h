//
// Created by elliot on 10/2/26.
//

#ifndef INDEX_FILERECORD_H
#define INDEX_FILERECORD_H

#include <cstdint>
#include <limits>

#include "FileFlags.h"

/**
 * RecordId is the unique identifier for a FileRecord entry.
 */
using RecordId = std::uint64_t;


inline constexpr RecordId ROOT_ID = 0;
inline constexpr RecordId INVALID_ID = std::numeric_limits<RecordId>::max();




struct FileRecord {
    RecordId id;

    /**
     * Parent's record id.
     * Used to recreate path topology.
     */
    RecordId parent_id;

    uint64_t name_offset;

    /**
     * File information (Dir, File, etc).
     */
    FileFlags flags;

};


#endif //INDEX_FILERECORD_H
