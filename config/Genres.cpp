#include "Genres.h"

namespace config {

bool operator==(const Genres& lhs, const Genres& rhs)
{
    return lhs.maximumGenreCount == rhs.maximumGenreCount &&
            lhs.minimumGenreWeight == rhs.minimumGenreWeight &&
            lhs.whitelistWeight == rhs.whitelistWeight &&
            lhs.whitelist == rhs.whitelist &&
            lhs.blacklist == rhs.blacklist;
}

} // namespace config
