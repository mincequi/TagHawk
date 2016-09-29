#include "Tags.h"


namespace config {

bool operator==(const Tags& lhs, const Tags& rhs)
{
    return lhs.stripId3v1 == rhs.stripId3v1;
}

} // namespace config
