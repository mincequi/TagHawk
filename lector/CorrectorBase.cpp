#include "CorrectorBase.h"

#include <QMap>

CorrectorBase::CorrectorBase(QObject *parent) : QObject(parent)
{
}

void CorrectorBase::getArtist(const QString& artist_)
{
    emit artist(artist_, artist_);
}

void CorrectorBase::getAlbum(const QString& artist_, const QString& album_)
{
    emit album(artist_, album_, album_);
}

void CorrectorBase::getGenres(const QString& artist_)
{
    emit genres(artist_, QMap<int, QString>());
}

void CorrectorBase::getYear(const QString& artist_, const QString& album_)
{
    emit album(artist_, album_, QString());
}
