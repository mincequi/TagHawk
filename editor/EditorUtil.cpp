#include "EditorUtil.h"

#include <QStandardItem>

#include "EditorDefines.h"


namespace editor {

QList<QStandardItem*> prepareRow(const QString& artist, const QMap<int, QString>& genres)
{
    if (genres.empty()) {
        return QList<QStandardItem*>();
    }

    // Create artist row with single genre item
    QList<QStandardItem*> artistRow;
    QStandardItem* genreItem = new QStandardItem(genres.last());
    genreItem->setData(ArtistItem, TypeRole);
    genreItem->setData(QString::number(genres.lastKey()), WeightRole);
    QStandardItem* checkboxItem = new QStandardItem(true);
    checkboxItem->setCheckable(true);
    checkboxItem->setCheckState(Qt::Unchecked);
    artistRow << genreItem << new QStandardItem(QString::number(genres.lastKey())) << new QStandardItem(artist) << checkboxItem;

    // If only one genre provided, we do not add children
    if (genres.size() == 1) {
        return artistRow;
    }

    // More than one genre provided, add children
    QMapIterator<int, QString> it(genres);
    it.toBack();
    while (it.hasPrevious()) {
        it.previous();
        QList<QStandardItem*> genreRow;
        QStandardItem* genreItem = new QStandardItem(it.value());
        genreItem->setData(GenreItem, TypeRole);
        genreItem->setData(QString::number(it.key()), WeightRole);
        genreRow << genreItem << new QStandardItem(QString::number(it.key()));
        artistRow.first()->appendRow(genreRow);
    }

    return artistRow;
}

} // namespace editor
