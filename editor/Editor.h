#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class QAbstractItemModel;
class QStandardItemModel;

namespace editor {

class Editor : public QObject
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = 0);

    QAbstractItemModel* genreModel();

signals:

public slots:
    // Artist correction is applied collection wide. It will not be specific to an album or whatever.
    void correctArtist(const QString& misspelled, const QString& corrected);
    // Album correction is limited to provided artist name.
    void correctAlbum(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum);
    // Genres are applied artist wide. There is no album specific genre.
    void setGenres(const QString& artist, const QMap<int, QString>& genres);
    // Year is applied to specified album from specified artist.
    void setYear(const QString& artist, const QString& album, const QString& year);

private:
    QStandardItemModel* m_genreModel;
};

} // namespace editor

#endif // EDITOR_H
