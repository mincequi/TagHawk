#include "Collection.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <iostream>

Collection::Collection(QObject *parent) :
    QObject(parent),
    m_reader(*this),
    m_writer(*this),
    m_size(0),
    m_db(QSqlDatabase::addDatabase("QSQLITE", "collection")),
    m_insertQuery(nullptr)
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
    m_insertQuery->prepare("INSERT INTO collection (fileName, artist, album, track, title, year, genre, stripId3v1, forceWrite) "
                           "VALUES (:fileName, :artist, :album, :track, :title, :year, :genre, :stripId3v1, :forceWrite)");
}

Collection::~Collection()
{
    if (m_insertQuery) {
        delete m_insertQuery;
        m_insertQuery = nullptr;
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

bool Collection::isEmpty()
{
    return m_size == 0;
}

void Collection::clear()
{
    QSqlQuery query(m_db);
    query.exec("DELETE FROM collection");
    query.exec("VACUUM");

    m_size = 0;
    emit sizeChanged(m_size);
}

void Collection::clearChanges()
{
    QSqlQuery query(m_db);
    query.exec("UPDATE collection SET artist_new = NULL, album_new = NULL, track_new = NULL, title_new = NULL, year_new = NULL, genre_new = NULL");
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

    // If we finished adding current artist, emit a signal
    if (!m_lastArtist.isEmpty() && m_lastArtist != artist) {
        emit artistAdded(m_lastArtist);
    }
    m_lastArtist = artist;

    ++m_size;
    emit sizeChanged(m_size);
}

std::list<Collection::Entry> Collection::entries() const
{
    QSqlQuery query(m_db);
    query.exec("SELECT fileName, artist, album, track, title, year, genre, "
               "artist_new, album_new, track_new, title_new, year_new, genre_new, "
               "stripId3v1, forceWrite "
               "FROM collection WHERE "
               "artist_new IS NOT NULL OR album_new IS NOT NULL OR track_new IS NOT NULL OR title_new IS NOT NULL OR year_new IS NOT NULL OR genre_new IS NOT NULL OR stripId3v1=\'1\' OR forceWrite=\'1\'");

    std::list<Entry> entries;
    while (query.next()) {
        entries.push_back(Entry { query.value(0).toString(),
                                  query.value(1).toString(), query.value(2).toString(), query.value(3).toInt(), query.value(4).toString(), query.value(5).toInt(), query.value(6).toString(),
                                  query.value(7).toString(), query.value(8).toString(), query.value(9).toInt(), query.value(10).toString(), query.value(11).toInt(), query.value(12).toString(),
                                  query.value(13).toBool(), query.value(14).toBool() });
    }

    return entries;
}

void Collection::renameArtist(const QString& artist, const QString& newName, int* rows)
{
    QSqlQuery query(m_db);

    bool success = query.prepare("UPDATE collection SET artist_new = :artist_new WHERE artist = :artist");
    query.bindValue(":artist", artist);
    query.bindValue(":artist_new", newName);
    success = query.exec();
    *rows = query.numRowsAffected();

    Q_UNUSED(success)
}

void Collection::categorizeArtist(const QString& artist, const QString& genre, int* rows)
{
    QSqlQuery query(m_db);

    bool success(false);
    success = query.prepare("UPDATE collection SET genre_new = NULL WHERE artist = :artist");
    query.bindValue(":artist", artist);
    success = query.exec();

    success = query.prepare("UPDATE collection SET genre_new = :genre WHERE artist = :artist AND genre <> :genre");
    query.bindValue(":artist", artist);
    query.bindValue(":genre", genre);
    success = query.exec();
    *rows += query.numRowsAffected();

    Q_UNUSED(success)
}
