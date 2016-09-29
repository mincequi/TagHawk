#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class QStandardItemModel;
class QTreeView;
class CorrectArtistsView;


namespace editor {

class Editor : public QObject
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = 0);

    void clear();
    void save();

    QWidget* createGenrefyArtistsView(QWidget* parent = 0);
    QWidget* createAmbiguousTagsView(QWidget* parent = 0);
    QWidget* createCorrectArtistsView(QWidget* parent = 0);

signals:
    void jobCountChanged(int count);
    void genreBlacklisted(const QString& genre);
    void genreWhitelisted(const QString& genre);

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
    void setupGenreModel();
    void setupGenreSampleData();

    void onGenreDoubleClicked(const QModelIndex& index);
    void onContextMenuRequested(const QPoint& pos);

    QStandardItemModel* m_genreModel;
    QTreeView*          m_genreView;
    QTreeView*          m_ambiguousTagsView;
    CorrectArtistsView* m_correctArtistsView;
};

} // namespace editor

#endif // EDITOR_H
