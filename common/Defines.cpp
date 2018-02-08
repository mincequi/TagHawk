#include "Defines.h"

QString toString(Field column)
{
    switch (column) {
    case Field::OriginalArtist:    return "artist";
    case Field::CanonicalArtist:    return "artist_new";
    case Field::Album:     return "album";
    case Field::Genre:     return "genre";
    case Field::Year:      return "year";
    }

    return QString();
}

QString toString(UseCase useCase)
{
    switch (useCase) {
    case UseCase::CorrectArtist:    return "Correct artist";
    case UseCase::CategorizeArtist: return "Categorize artist";
    case UseCase::CorrectAlbum:     return "Correct album";
    case UseCase::DateAlbum:        return "Date album";
    }

    return QString();
}
