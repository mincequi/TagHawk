#include "Genres.h"

namespace config {

bool operator==(const Genres& lhs, const Genres& rhs)
{
    return lhs.maximumGenreCount == rhs.maximumGenreCount &&
            lhs.minimumGenreWeight == rhs.minimumGenreWeight &&
            lhs.autoConfirmWeight == rhs.autoConfirmWeight &&
            lhs.whitelist == rhs.whitelist &&
            lhs.blacklist == rhs.blacklist;
}

} // namespace config
