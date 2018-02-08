#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#include <QString>

enum class Field {
    OriginalArtist,
    CanonicalArtist,
    Album,
    Genre,
    Year
};

QString toString(Field column);

enum class UseCase {
    CorrectArtist,
    CategorizeArtist,
    CorrectAlbum,
    DateAlbum
};

QString toString(UseCase useCase);

#endif // COMMONDEFINES_H
