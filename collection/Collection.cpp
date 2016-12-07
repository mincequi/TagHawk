#include "Collection.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <iostream>

#include "JobsModel.h"


namespace collection {

Collection::Collection(QObject *parent) :
    QObject(parent),
    m_reader(*this),
    m_writer(*this),
    m_jobsModel(new JobsModel(this)),
    m_size(0),
    m_db(QSqlDatabase::addDatabase("QSQLITE", "collection")),
    m_insertQuery(nullptr),
    m_selectArtistInconsistenciesQuery(nullptr),
    m_selectGenreInconsistenciesQuery(nullptr)
{
    m_db.setDatabaseName(":memory:");

    if (!m_db.open()) {
        qWarning() << "Cannot open database:" << m_db.lastError();
        m_db = QSqlDatabase();
        return;
    }

    QString str("CREATE TABLE IF NOT EXISTS collection ("
                "fileName TEXT NOT NULL PRIMARY KEY, "
                "artist TEXT,    artist_new TEXT,    "
                "album  TEXT,    album_new  TEXT,    "
                "track  INTEGER, track_new  INTEGER, "
                "title  TEXT,    title_new  TEXT,    "
                "year   INTEGER, year_new   INTEGER, "
                "genre  TEXT,    genre_new  TEXT,    "
                "stripId3v1 INTEGER,"
                "forceWrite INTEGER"
                ")");
    m_db.exec(str);

    m_insertQuery = new QSqlQuery(m_db);
    m_insertQuery->prepare("INSERT INTO collection (fileName, artist, album, track, title, year, genre, stripId3v1, forceWrite) VALUES (:fileName, :artist, :album, :track, :title, :year, :genre, :stripId3v1, :forceWrite)");

    m_selectGenreInconsistenciesQuery = new QSqlQuery(m_db);
    m_selectGenreInconsistenciesQuery->prepare("SELECT DISTINCT genre FROM collection WHERE artist = :artist AND genre != :genre");
}

Collection::~Collection()
{
    if (m_insertQuery) {
        delete m_insertQuery;
        m_insertQuery = nullptr;
    }

    if (m_selectGenreInconsistenciesQuery) {
        delete m_selectGenreInconsistenciesQuery;
        m_selectGenreInconsistenciesQuery = nullptr;
    }
}

AbstractReader& Collection::reader()
{
    return m_reader;
}

AbstractWriter& Collection::writer()
{
    return m_writer;
}

JobsModel* Collection::jobsModel()
{
    return m_jobsModel;
}

bool Collection::isEmpty()
{
    return m_size == 0;
}

void Collection::rescan()
{
}

void Collection::clear()
{
    m_size = 0;
    emit sizeChanged(m_size);
}

void Collection::beginWriting()
{
    m_lastArtist.clear();
    m_lastAlbum.clear();
}

void Collection::endWriting()
{
    if (!m_lastArtist.isEmpty()) {
        emit artistAdded(m_lastArtist);
    }
    m_lastArtist.clear();

    if (m_lastAlbum.isValid()) {
        emit albumAdded(m_lastAlbum);
    }
    m_lastAlbum.clear();
}

void Collection::beginReading()
{
}

void Collection::endReading()
{
}

void Collection::appendEntry(const QString& fileName,
                             const QString& artist,
                             const QString& album,
                             std::int16_t   track,
                             const QString& title,
                             std::int16_t   year,
                             const QString& genre,
                             bool           stripId3v1,
                             bool           forceWrite)
{
    if (!m_lastArtist.isEmpty() && m_lastArtist != artist) {
        emit artistAdded(m_lastArtist);
    }
    m_lastArtist = artist;

    AlbumTag albumTag { artist, album, year, genre };
    if (m_lastAlbum.isValid() && m_lastAlbum != albumTag) {
        emit albumAdded(m_lastAlbum);
    }
    m_lastAlbum = albumTag;

    m_insertQuery->bindValue(":fileName",   fileName);
    m_insertQuery->bindValue(":artist",     artist);
    m_insertQuery->bindValue(":album",      album);
    m_insertQuery->bindValue(":track",      track);
    m_insertQuery->bindValue(":title",      title);
    m_insertQuery->bindValue(":year",       year);
    m_insertQuery->bindValue(":genre",      genre);
    m_insertQuery->bindValue(":stripId3v1", stripId3v1);
    m_insertQuery->bindValue(":forceWrite", forceWrite);
    m_insertQuery->exec();

    ++m_size;
    emit sizeChanged(m_size);
}

void Collection::renameArtist(const QString& artist, const QString& newName)
{
    QSqlQuery query(m_db);
    bool success = query.prepare("UPDATE collection SET artist_new = :artist_new WHERE artist = :artist");
    query.bindValue(":artist", artist);
    query.bindValue(":artist_new", newName);
    success = query.exec();
}

void Collection::categorizeArtist(const QString& artist, const QString& genre)
{
    QSqlQuery query(m_db);
    bool success = query.prepare("UPDATE collection SET genre_new = :genre_new WHERE artist = :artist");
    query.bindValue(":artist", artist);
    query.bindValue(":genre_new", genre);
    success = query.exec();
}

QStringList Collection::selectFiles(const QString& artist, const QString& genre)
{
    QSqlQuery query(m_db);

    query.prepare("SELECT fileName FROM collection WHERE artist = :artist AND genre = :genre ORDER BY fileName ASC");
    query.bindValue(":artist",   artist);
    query.bindValue(":genre",    genre);
    query.exec();

    QStringList files;
    while (query.next()) {
        files << query.value(0).toString();
    }

    return files;
}

} // namespace collection
