#include "LastFmCache.h"

#include <QDataStream>
#include <QDir>
#include <QSqlQuery>
#include <QStandardPaths>

#include "Defines.h"

#include "cache/Cache.h"
#include "common/DatabaseUtil.h"


namespace scraper {
namespace lastfm {

LastFmCache::LastFmCache()
{
    database::createKeyValueTable(Cache::instance().db(), scraper::lastfm::cacheTableArtistCorrection);
    database::createKeyValueTable(Cache::instance().db(), scraper::lastfm::cacheTableArtistTopTags);
}

LastFmCache::~LastFmCache()
{
}

LastFmCache::Artist::Artist()
{
}

LastFmCache::Artist::~Artist()
{
}

QString LastFmCache::Artist::getCorrection(const QString& artist)
{
    return database::select(Cache::instance().db(), cacheTableArtistCorrection, artist.toLower());
}

void LastFmCache::Artist::setCorrection(const QString& misspelled, const QString& corrected)
{
    database::insert(Cache::instance().db(), cacheTableArtistCorrection, misspelled.toLower(), corrected);
}

QMap<int, QString> LastFmCache::Artist::getTopTags(const QString& artist)
{
    QByteArray byteArray = database::select(Cache::instance().db(), cacheTableArtistTopTags, artist);
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

    database::insert(Cache::instance().db(), cacheTableArtistTopTags, artist, byteArray);
}

} // namespace lastfm
} // namespace scraper
