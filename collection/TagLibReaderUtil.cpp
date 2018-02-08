#include "TagLibReaderUtil.h"

bool operator==(const TagLib::ID3v1::Tag& v1, const TagLib::ID3v2::Tag& v2)
{
    // Case insensitive comparsion of most tags
    // Check wether v1 is a sub-set of v2 tags.

    bool equal = true;
    if (!v1.title().isEmpty()) {
        equal &= v2.title().upper().find(v1.title().upper()) != -1;
    }
    if (!v1.artist().isEmpty()) {
        equal &= v2.artist().upper().find(v1.artist().upper()) != -1;
    }
    if (!v1.album().isEmpty()) {
        equal &= v2.album().upper().find(v1.album().upper()) != -1;
    }
    // special case for genre: only signal difference if v1 carries a genre but v2 not.
    if (!v1.genre().isEmpty() && v2.genre().isEmpty()) {
        equal = false;
    }
    if (v1.year() > 0) {
        equal &= v1.year() == v2.year();
    }
    if (v1.track() > 0) {
        equal &= v1.track()  == v2.track();
    }

    return equal;
}

std::ostream& operator<< (std::ostream& stream, const TagLib::Tag& tag)
{
    stream << "artist: " << tag.artist().to8Bit() << std::endl;
    stream << "album:  " << tag.album().to8Bit() << std::endl;
    stream << "track:  " << tag.track() << std::endl;
    stream << "title:  " << tag.title().to8Bit() << std::endl;
    stream << "genre:  " << tag.genre().to8Bit() << std::endl;
    stream << "year:   " << tag.year() << std::endl;
    return stream;
}
