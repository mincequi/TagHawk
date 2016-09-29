#ifndef COLLECTION_H
#define COLLECTION_H

#include <cstdint>

#include <QObject>
#include <QSqlDatabase>

#include "types/AlbumTag.h"


class QString;

class Collection : public QObject
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);

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
                     const QString& genre);

signals:
    void artistAdded(const QString& artist);
    void albumAdded(const AlbumTag& album);

public slots:

private:
    void openDatabase();

    QString         m_lastArtist;
    AlbumTag        m_lastAlbum;
    QSqlDatabase    m_database;
};

#endif // COLLECTION_H
