#include "CategorizeArtistModel.h"

#include "CategorizeArtistDefines.h"

#include <QDebug>

#include "config/Config.h"

CategorizeArtistModel::CategorizeArtistModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

CategorizeArtistModel::~CategorizeArtistModel()
{
}

QVariant CategorizeArtistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    return static_cast<CategorizeArtistItem*>(index.internalPointer())->data(index.column(), role);
}

bool CategorizeArtistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());
    if (!item) {
        return false;
    }

    return item->setData(index, value, role);
}

QVariant CategorizeArtistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_rootItem.data(section, role);
}

QModelIndex CategorizeArtistModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    // This is an artist item
    if (!parent.isValid()) {
        return createIndex(row, column, m_artistItems[row]);
    }

    CategorizeArtistItem* parentItem = static_cast<CategorizeArtistItem*>(parent.internalPointer());
    return createIndex(row, column, parentItem->genreItems()[row]);
}

QModelIndex CategorizeArtistModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());

    switch (item->type()) {
    case CategorizeArtistItem::Type::Genre:
    {
        CategorizeArtistItem* artistItem = item->artistItem();
        return createIndex(m_artistItems.indexOf(artistItem), GenreColumn, artistItem);
    }
    case CategorizeArtistItem::Type::Root:
    case CategorizeArtistItem::Type::Artist:
    default:
        return QModelIndex();
    }
}

int CategorizeArtistModel::rowCount(const QModelIndex &parent) const
{
    // If root item, return artist count
    if (!parent.isValid()) {
        return m_artistItems.size();
    }

    // Only return rowCount for genres
    if (parent.column() != GenreColumn) {
        return 0;
    }

    return static_cast<CategorizeArtistItem*>(parent.internalPointer())->genreItems().count();
}

int CategorizeArtistModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 5;
    }

    return 2;
}

Qt::ItemFlags CategorizeArtistModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    if (index.column() == GenreColumn) {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

    if (index.column() == ConfirmedColumn) {
        return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    }

    return QAbstractItemModel::flags(index);
}

void CategorizeArtistModel::setGenres(const QString& artist, const QMap<int, QString>& genres)
{
    qDebug() << "Genres for artist" << artist << ":" << genres;

    beginInsertRows(QModelIndex(), m_artistItems.size(), m_artistItems.size());
    CategorizeArtistItem* artistItem = find(artist);
    if (!artistItem) {
        artistItem = new CategorizeArtistItem(this, artist, genres);
        m_artistItems.push_back(artistItem);
    }

    artistItem->setConfirmed(genres.lastKey() >= Config::instance().genres().autoConfirmWeight);
    endInsertRows();
}

CategorizeArtistItem* CategorizeArtistModel::find(const QString& artist)
{
    for (CategorizeArtistItem* artistItem : m_artistItems) {
        if (artistItem->data(ArtistColumn) == artist) {
            return artistItem;
        }
    }

    return nullptr;
}
