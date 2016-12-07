#include "TagLibReaderUtil.h"


namespace collection
{

TagLib::ID3v2::Tag& operator+=(TagLib::ID3v2::Tag& lhs, const TagLib::ID3v2::Tag& rhs)
{
    if (rhs.isEmpty()) {
        return lhs;
    }

    if (!rhs.title().isEmpty()) {
        lhs.setTitle(rhs.title());
    }
    if (!rhs.artist().isEmpty()) {
        lhs.setArtist(rhs.artist());
    }
    if (!rhs.album().isEmpty()) {
        lhs.setAlbum(rhs.album());
    }
    if (!rhs.comment().isEmpty()) {
        lhs.setComment(rhs.comment());
    }
    if (!rhs.genre().isEmpty()) {
        lhs.setGenre(rhs.genre());
    }
    if (rhs.year() != 0) {
        lhs.setYear(rhs.year());
    }
    if (rhs.track() != 0) {
        lhs.setTrack(rhs.track());
    }

    return lhs;
}

} // namespace collection
