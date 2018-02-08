#include "CategorizeArtistsModel.h"

#include "CategorizeArtistsDefines.h"

#include <QDebug>

#include "config/Config.h"

CategorizeArtistsModel::CategorizeArtistsModel(QObject *parent)
    : QAbstractItemModel(parent),
      m_config(Config::instance().genres())
{
    connect(&Config::instance(), &Config::genresChanged, this, &CategorizeArtistsModel::onConfigChanged);

    connect(this, &CategorizeArtistsModel::dataChanged, [this](const QModelIndex& index) {
        CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());
        if (!item->artist().isEmpty()) {
            int numFiles = 0;
            emit artistCategorized(item->artist(), item->genre(), &numFiles);
            item->setNumAffectedFiles(numFiles);
        }
    });
}

CategorizeArtistsModel::~CategorizeArtistsModel()
{
}

QVariant CategorizeArtistsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    return static_cast<CategorizeArtistItem*>(index.internalPointer())->data(index.column(), role);
}

bool CategorizeArtistsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());
    if (item->type() != CategorizeArtistItem::Type::Artist) {
        return false;
    }

    if (role == Qt::EditRole && index.column() == GenreColumn) {
         item->setUserGenre(value.toString());
         emit dataChanged(index, index);
         return true;
    }

    if (role == Qt::CheckStateRole && index.column() == ConfirmedColumn) {
         item->setConfirmed(value == Qt::Checked);
         emit dataChanged(index, index);
         return true;
    }

    return false;
}

QVariant CategorizeArtistsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_rootItem.data(section, role);
}

QModelIndex CategorizeArtistsModel::index(int row, int column, const QModelIndex& parent) const
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

QModelIndex CategorizeArtistsModel::parent(const QModelIndex &index) const
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

int CategorizeArtistsModel::rowCount(const QModelIndex &parent) const
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

int CategorizeArtistsModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 5;
    }

    return 2;
}

Qt::ItemFlags CategorizeArtistsModel::flags(const QModelIndex &index) const
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

void CategorizeArtistsModel::setGenres(const QString& artist, const QMap<int, QString>& genres)
{
    qDebug() << "Genres for artist" << artist << ":" << genres;

    beginInsertRows(QModelIndex(), m_artistItems.size(), m_artistItems.size());
    CategorizeArtistItem* artistItem = find(artist);
    if (!artistItem) {
        artistItem = new CategorizeArtistItem(artist, genres, m_config.autoConfirmWeight);
        m_artistItems.push_back(artistItem);
    }

    if (!artistItem->genre().isEmpty()) {
        int numFiles = 0;
        emit artistCategorized(artist, artistItem->genre(), &numFiles);
        artistItem->setNumAffectedFiles(numFiles);
    }
    endInsertRows();
}

CategorizeArtistItem* CategorizeArtistsModel::find(const QString& artist)
{
    for (CategorizeArtistItem* artistItem : m_artistItems) {
        if (artistItem->data(ArtistColumn) == artist) {
            return artistItem;
        }
    }

    return nullptr;
}

void CategorizeArtistsModel::onConfigChanged()
{
    m_config = Config::instance().genres();
}
