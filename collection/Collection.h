#ifndef COLLECTION_H
#define COLLECTION_H

#include <cstdint>

#include <QObject>
#include <QSqlDatabase>

#include "TagLibReader.h"
#include "TagLibWriter.h"
#include "common/AlbumTag.h"

class JobsModel;


namespace collection {

class Collection : public QObject
{
    Q_OBJECT

public:
    explicit Collection(QObject *parent = 0);
    ~Collection();

    AbstractReader& reader();
    AbstractWriter& writer();
    JobsModel*      jobsModel();

    bool isEmpty();
    void rescan();
    void clear();

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

    void renameArtist(const QString& oldName, const QString& newName);
    void categorizeArtist(const QString& artist, const QString& genre);

    QStringList selectFiles(const QString& artist, const QString& genre);


signals:
    void sizeChanged(size_t size);
    void artistAdded(const QString& artist);
    void albumAdded(const AlbumTag& album);

private:
    void openDatabase();

    TagLibReader    m_reader;
    TagLibWriter    m_writer;
    JobsModel*      m_jobsModel;

    int             m_size;

    QString         m_lastArtist;
    AlbumTag        m_lastAlbum;
    QSqlDatabase    m_db;
    QSqlQuery*      m_insertQuery;
    QSqlQuery*      m_selectArtistInconsistenciesQuery;
    QSqlQuery*      m_selectGenreInconsistenciesQuery;
};

} // namespace collection

#endif // COLLECTION_H
