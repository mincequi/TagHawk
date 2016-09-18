#ifndef LASTFMCACHE_H
#define LASTFMCACHE_H

#include <QMap>
#include <QSqlDatabase>

class QAbstractItemModel;
class QSqlQueryModel;


namespace scraper {
namespace lastfm {

class LastFmCache
{
public:
    LastFmCache();
    ~LastFmCache();

    class Artist
    {
    public:
        Artist();
        ~Artist();

        QString             getCorrection(const QString& artist);
        void                setCorrection(const QString& misspelled, const QString& corrected);
        QMap<int, QString>  getTopTags(const QString& artist);
        void                setTopTags(const QString& artist, const QMap<int, QString>& tags);

    private:
        QSqlDatabase    m_db;
        QSqlQueryModel* m_correctionModel;
        QSqlQueryModel* m_topTagsModel;
    } artist;
};

} // namespace lastfm
} // namespace scraper

#endif // LASTFMCACHE_H
