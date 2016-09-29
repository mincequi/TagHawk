#ifndef TAGS_H
#define TAGS_H

#include <QStringList>


namespace config {

struct Tags
{
    bool stripId3v1;
};
bool operator==(const Tags& lhs, const Tags& rhs);

} // namespace config

#endif // TAGS_H
