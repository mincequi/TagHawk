#ifndef COLLECTION_H
#define COLLECTION_H

#include <cstdint>

#include <QObject>
#include <QSqlDatabase>

#include "TagLibReader.h"
#include "TagLibWriter.h"
#include <common/AlbumTag.h>

class Collection : public QObject
{
    Q_OBJECT

public:
    struct Entry {
        QString         fileName;   // 0

        QString         artist;     // 1
        QString         album;
        std::int32_t    track;
        QString         title;
        std::int32_t    year;
        QString         genre;      // 6

        QString         newArtist;  // 7
        QString         newAlbum;
        std::int32_t    newTrack;
        QString         newTitle;
        std::int32_t    newYear;
        QString         newGenre;   // 12

        bool            stripId3v1; // 13
        bool            forceWrite; // 14
    };

    explicit Collection(QObject *parent = 0);
    ~Collection();

    AbstractReader& reader();
    AbstractWriter& writer();

    bool isEmpty();
    void clear();
    void clearChanges();

    void beginWriting();
    void endWriting();

    void beginReading();
    void endReading();

    void appendEntry(const QString& fileName,
                     const QString& artist,
                     const QString& album,
                     std::int16_t   track,
                     const QString& title,
                     std::int16_t   year,
                     const QString& genre,
                     bool           stripId3v1,
                     bool           forceWrite);

    std::list<Entry> entries() const;

    void renameArtist(const QString& oldName, const QString& newName, int* rows);
    void categorizeArtist(const QString& artist, const QString& genre, int* rows);

signals:
    void sizeChanged(size_t size);
    void artistAdded(const QString& artist);
    void albumAdded(const AlbumTag& album);

private:
    void openDatabase();

    TagLibReader    m_reader;
    TagLibWriter    m_writer;

    int             m_size;

    QString         m_lastArtist;
    AlbumTag        m_lastAlbum;
    QSqlDatabase    m_db;
    QSqlQuery*      m_insertQuery;
};

#endif // COLLECTION_H
