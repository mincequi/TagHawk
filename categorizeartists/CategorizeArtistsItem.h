#ifndef CATEGORIZEARTISTSITEM_H
#define CATEGORIZEARTISTSITEM_H

#include <QList>
#include <QVariant>

class CategorizeArtistItem
{
public:
    enum class Type {
        Root,
        Artist,
        Genre
    };

    CategorizeArtistItem();
    CategorizeArtistItem(const QString& artist, const QMap<int, QString>& genres, int autoConfirmWeight);
    ~CategorizeArtistItem();

    /// Type of Item
    Type type() const;

    /// General data accessor
    QVariant data(int section, int role = Qt::DisplayRole) const;

    /// Get artist (only valid for artist item).
    QString artist() const;

    /// Get associated artist item (only valid for genre item).
    CategorizeArtistItem* artistItem() const;

    /// Get selected and confirmed genre (only valid for artist item).
    QString genre() const;

    /// Get associated genres (only valid for artist item).
    const QList<CategorizeArtistItem*> genreItems() const;

    /// Set (child-) genre (only valid for artist item).
    void activateGenre(const CategorizeArtistItem* genreItem);

    /// Set custom genre (only valid for artist item).
    void setUserGenre(const QString& genre);

    /// Set confirmation flag (only valid for artist item).
    void setConfirmed(bool isConfirmed);

    /// Set number of affected files for change (only valid for artist item).
    void setNumAffectedFiles(int numFiles);

private:
    Type                            m_type;
    CategorizeArtistItem*           m_parent;
    QList<CategorizeArtistItem*>    m_children;

    QString m_artist;
    QString m_genre;
    int     m_weight;
    bool    m_isConfirmed;
    int     m_numAffectedFiles;
};

#endif // CATEGORIZEARTISTSITEM_H
