#include "Collection.h"

#include <QString>
#include <iostream>


Collection::Collection(QObject *parent) :
    QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "collection");
    m_database.setDatabaseName(":memory:");
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
                           const QString& genre)
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

    //std::cout << "Filename: " << fileName.toUtf8().constData() << ", ";
    //std::cout << "Artist: " << artist.toUtf8().constData() << ", ";
    //std::cout << "Album: " << album.toUtf8().constData() << ", ";
    //std::cout << "Track: " << track << ", ";
    //std::cout << "Title: " << title.toUtf8().constData() << ", ";
    //std::cout << "Year: " << year << ", ";
    //std::cout << "Genre: " << genre.toUtf8().constData() << std::endl;
}
