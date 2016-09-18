#include "LastFmCache.h"

#include "Defines.h"

#include <common/DatabaseUtil.h>

#include <QDataStream>
#include <QDir>
#include <QSqlQuery>
#include <QStandardPaths>


namespace scraper {
namespace lastfm {

LastFmCache::LastFmCache()
{
}

LastFmCache::~LastFmCache()
{
}

LastFmCache::Artist::Artist()
    : m_db(::database::openCache())
{
}

LastFmCache::Artist::~Artist()
{
}

QString LastFmCache::Artist::getCorrection(const QString& artist)
{
    return database::select(m_db, cacheTableArtistCorrection, artist.toLower());
}

void LastFmCache::Artist::setCorrection(const QString& misspelled, const QString& corrected)
{
    database::insert(m_db, cacheTableArtistCorrection, misspelled.toLower(), corrected);
}

QMap<int, QString> LastFmCache::Artist::getTopTags(const QString& artist)
{
    QByteArray byteArray = database::select(m_db, cacheTableArtistTopTags, artist);
    QDataStream stream(byteArray);

    QMap<int, QString> map;
    stream >> map;

    return map;
}

void LastFmCache::Artist::setTopTags(const QString& artist, const QMap<int, QString>& tags)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << tags;
    qDebug() << "Inserted" << tags.size() << "tags for" << "artist:" << artist;

    database::insert(m_db, cacheTableArtistTopTags, artist, byteArray);
}

} // namespace lastfm
} // namespace scraper
