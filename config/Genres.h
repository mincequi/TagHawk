#ifndef GENRES_H
#define GENRES_H

#include <QStringList>


namespace config {

struct Genres
{
    int maximumGenreCount;
    int minimumGenreWeight;
    int autoConfirmWeight;

    QStringList whitelist;
    QStringList blacklist;
};
bool operator==(const Genres& lhs, const Genres& rhs);

} // namespace config

#endif // GENRES_H
