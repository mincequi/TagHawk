#include "Editor.h"

#include <QDebug>
#include <QStandardItemModel>

#include "EditorUtil.h"


namespace editor {

Editor::Editor(QObject *parent)
    : QObject(parent),
      m_genreModel(new QStandardItemModel(this))
{
}

QAbstractItemModel* Editor::genreModel()
{
    return m_genreModel;
}

void Editor::correctArtist(const QString& misspelled, const QString& corrected)
{
    qDebug() << "Correct artist" << misspelled << "->" << corrected;
}

void Editor::correctAlbum(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum)
{
}

void Editor::setGenres(const QString& artist, const QMap<int, QString>& genres)
{
    qDebug() << "Genres for artist" << artist << ":" << genres;

    // 1. Find existing entry

    // 1.1 If exists, modify it

    // 1.2 if not append a new line
    auto editStringList = toEditStringList(genres);

    QStandardItem* genre = new QStandardItem(editStringList.isEmpty() ? QString("<no genre available>") : editStringList.first());
    genre->setData(toDisplayStringList(genres), Qt::UserRole+1);
    genre->setData(editStringList, Qt::UserRole+2);
    m_genreModel->appendRow( { new QStandardItem(artist), genre } );
}

void Editor::setYear(const QString& artist, const QString& album, const QString& year)
{
}

} // namespace editor
