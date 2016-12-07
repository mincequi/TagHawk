#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class CorrectArtistsModel;
class CategorizeArtistsModel;
class JobsModel;
class QTreeView;


namespace editor {

class Editor : public QObject
{
    Q_OBJECT

public:
    explicit Editor(QObject *parent = 0);

    CorrectArtistsModel*    correctArtistsModel();
    CategorizeArtistsModel* categorizeArtistsModel();

    void clear();

public slots:
    // Album correction is limited to provided artist name.
    void correctAlbum(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum);
    // Year is applied to specified album from specified artist.
    void setYear(const QString& artist, const QString& album, const QString& year);

private:
    void onGenreDoubleClicked(const QModelIndex& index);
    void onContextMenuRequested(const QPoint& pos);

    CorrectArtistsModel*    m_correctArtistsModel;
    CategorizeArtistsModel* m_categorizeArtistsModel;
    QTreeView*          m_genreView;
    QTreeView*          m_ambiguousTagsView;
};

} // namespace editor

#endif // EDITOR_H
