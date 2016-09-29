#include "AlbumTag.h"

AlbumTag::AlbumTag(const QString& artist_, const QString& album_, std::int16_t year_, const QString& genre_)
    : artist(artist_),
      album(album_),
      year(year_),
      genre(genre_)
{
}

void AlbumTag::clear()
{
    artist.clear();
    album.clear();
    year = 0;
    genre.clear();
}

bool AlbumTag::isValid()
{
    return (!artist.isEmpty() && !album.isEmpty());
}

bool AlbumTag::operator==(const AlbumTag &other) const
{
    return (artist == other.artist &&
            album  == other.album);
}

bool AlbumTag::operator!=(const AlbumTag &other) const
{
    return (artist != other.artist ||
            album  != other.album);
}
