#include "CategorizeArtistsItem.h"

#include "CategorizeArtistsDefines.h"


CategorizeArtistItem::CategorizeArtistItem()
    : m_type(Type::Root),
      m_parent(nullptr),
      m_isConfirmed(false),
      m_numAffectedFiles(0)
{
}

CategorizeArtistItem::CategorizeArtistItem(const QString& artist, const QMap<int, QString>& genres, int autoConfirmWeight)
    : m_type(Type::Artist),
      m_artist(artist),
      m_isConfirmed(false),
      m_numAffectedFiles(0)
{
    if (genres.isEmpty()) {
        return;
    }

    m_genre = genres.last();
    m_weight = genres.lastKey();
    m_isConfirmed = genres.lastKey() >= autoConfirmWeight;

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

QString CategorizeArtistItem::artist() const
{
    return m_artist;
}

CategorizeArtistItem* CategorizeArtistItem::artistItem() const
{
    return m_parent;
}

QString CategorizeArtistItem::genre() const
{
    if (m_genre.isEmpty() || !m_isConfirmed) {
        return QString();
    }

    return m_genre;
}

const QList<CategorizeArtistItem*> CategorizeArtistItem::genreItems() const
{
    return m_children;
}

void CategorizeArtistItem::activateGenre(const CategorizeArtistItem* genreItem)
{
    if (m_type != Type::Artist || genreItem->type() != Type::Genre) {
        return;
    }

    m_genre = genreItem->m_genre;
    m_weight = genreItem->m_weight;
    m_isConfirmed = true;
}

void CategorizeArtistItem::setUserGenre(const QString& genre)
{
    if (m_type != Type::Artist) {
        return;
    }

    m_genre = genre;
    m_weight = 100;
    m_isConfirmed = true;
}

void CategorizeArtistItem::setConfirmed(bool isConfirmed)
{
    if (m_type != Type::Artist) {
        return;
    }

    m_isConfirmed = isConfirmed;
}

void CategorizeArtistItem::setNumAffectedFiles(int numFiles)
{
    m_numAffectedFiles = numFiles;
}
