#include <catch2/catch_test_macros.hpp>

#include "../File/FileFlags.h"

static_assert(has_flag(FileFlags::File | FileFlags::Dir, FileFlags::Dir));

TEST_CASE("operator| combines flags", "[flags]") {
    const FileFlags f = FileFlags::File | FileFlags::Hidden;

    CHECK(has_flag(f, FileFlags::File));
    CHECK(has_flag(f, FileFlags::Hidden));
    CHECK_FALSE(has_flag(f, FileFlags::Dir));
}

TEST_CASE("operator|= adds flags in place", "[flags]") {
    FileFlags f = FileFlags::Dir;

    SECTION("adding a new flag keeps the existing one") {
        f |= FileFlags::Hidden;
        CHECK(has_flag(f, FileFlags::Dir));
        CHECK(has_flag(f, FileFlags::Hidden));
    }

    SECTION("adding a flag that's already set changes nothing") {
        f |= FileFlags::Dir;
        CHECK(f == FileFlags::Dir);
    }
}