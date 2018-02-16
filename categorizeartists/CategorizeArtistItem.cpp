#include "CategorizeArtistItem.h"

#include "CategorizeArtistDefines.h"
#include "CategorizeArtistModel.h"

CategorizeArtistItem::CategorizeArtistItem()
    : m_model(nullptr),
      m_type(Type::Root),
      m_parent(nullptr),
      m_isConfirmed(false),
      m_numAffectedFiles(0)
{
}

CategorizeArtistItem::CategorizeArtistItem(CategorizeArtistModel* model, const QString& artist, const QMap<int, QString>& genres)
    : m_model(model),
      m_type(Type::Artist),
      m_artist(artist),
      m_isConfirmed(false),
      m_numAffectedFiles(0)
{
    if (genres.isEmpty()) {
        return;
    }

    m_genre = genres.last();
    m_weight = genres.lastKey();

    QMapIterator<int, QString> it(genres);
    it.toBack();
    while (it.hasPrevious()) {
        it.previous();

        CategorizeArtistItem* genreItem = new CategorizeArtistItem();
        genreItem->m_type = Type::Genre;
        genreItem->m_parent = this;
        genreItem->m_genre = it.value();
        genreItem->m_weight = it.key();

        m_children.append(genreItem);
    }
}

CategorizeArtistItem::~CategorizeArtistItem()
{
    qDeleteAll(m_children);
}

CategorizeArtistItem::Type CategorizeArtistItem::type() const
{
    return m_type;
}

QVariant CategorizeArtistItem::data(int section, int role) const
{
    // special handling for checkboxes in confirmation column
    if (m_type == Type::Artist && section == ConfirmedColumn && role == Qt::CheckStateRole) {
        return m_isConfirmed ? Qt::Checked : Qt::Unchecked;
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (m_type) {
    case Type::Root:
        switch (section) {
        case ArtistColumn:      return "Artist";
        case GenreColumn:       return "Genre";
        case WeightColumn:      return "Weight";
        case ConfirmedColumn:   return "Confirmed";
        case AffectedFilesColumn: return "Affected Files";
        }
    case Type::Artist:
        switch (section) {
        case ArtistColumn:      return m_artist;
        case GenreColumn:       return m_genre;
        case WeightColumn:      return m_weight > 0 ? m_weight : QVariant();
        case ConfirmedColumn:   return QVariant();
        case AffectedFilesColumn: return m_numAffectedFiles;
        }
    case Type::Genre:
        switch (section) {
        case ArtistColumn:      return QVariant();
        case GenreColumn:       return m_genre;
        case WeightColumn:      return m_weight;
        case ConfirmedColumn:   return QVariant();
        case AffectedFilesColumn: return QVariant();
        }
    }

    return QVariant();
}

bool CategorizeArtistItem::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (m_type != Type::Artist) {
        return false;
    }

    // Handle user edit
    if (role == Qt::EditRole && index.column() == GenreColumn) {
         m_genre = value.toString();
         m_weight = 100;
         m_isConfirmed = true;
         int numFiles = 0;
         emit m_model->artistCategorized(m_artist, m_genre, &numFiles);
         m_numAffectedFiles = numFiles;
         emit m_model->dataChanged(index, index.sibling(index.row(), AffectedFilesColumn));
         return true;
    }

    // Handle user confirmation
    if (role == Qt::CheckStateRole && index.column() == ConfirmedColumn) {
         m_isConfirmed = (value == Qt::Checked);
         int numFiles = 0;
         emit m_model->artistCategorized(m_artist, m_isConfirmed ? m_genre : QString(), &numFiles);
         m_numAffectedFiles = numFiles;
         emit m_model->dataChanged(index, index.sibling(index.row(), AffectedFilesColumn));
         return true;
    }

    return false;
}

void CategorizeArtistItem::setConfirmed(bool isConfirmed)
{
    m_isConfirmed = isConfirmed;

    if (m_isConfirmed) {
        int numFiles = 0;
        emit m_model->artistCategorized(m_artist, m_genre, &numFiles);
        m_numAffectedFiles = numFiles;
    }
}

CategorizeArtistItem* CategorizeArtistItem::artistItem() const
{
    return m_parent;
}

const QList<CategorizeArtistItem*> CategorizeArtistItem::genreItems() const
{
    return m_children;
}

void CategorizeArtistItem::activateGenre(const QModelIndex& index)
{
    CategorizeArtistItem* genreItem = static_cast<CategorizeArtistItem*>(index.internalPointer());
    if (!genreItem) {
        return;
    }

    if (m_type != Type::Artist || genreItem->type() != Type::Genre) {
        return;
    }

    m_genre = genreItem->m_genre;
    m_weight = genreItem->m_weight;
    m_isConfirmed = true;

    int numFiles = 0;
    emit m_model->artistCategorized(m_artist, m_genre, &numFiles);
    m_numAffectedFiles = numFiles;

    QModelIndex parentIndex = index.parent();
    emit m_model->dataChanged(parentIndex, parentIndex.sibling(parentIndex.row(), AffectedFilesColumn));
}
