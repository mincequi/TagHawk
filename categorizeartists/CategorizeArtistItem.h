#ifndef CATEGORIZEARTISTSITEM_H
#define CATEGORIZEARTISTSITEM_H

#include <QList>
#include <QVariant>

class CategorizeArtistModel;

class CategorizeArtistItem
{
public:
    enum class Type {
        Root,
        Artist,
        Genre
    };

    CategorizeArtistItem();
    CategorizeArtistItem(CategorizeArtistModel* model, const QString& artist, const QMap<int, QString>& genres);
    ~CategorizeArtistItem();

    /// Type of Item
    Type type() const;

    /// General data accessor
    QVariant    data(int section, int role = Qt::DisplayRole) const;
    bool        setData(const QModelIndex &index, const QVariant &value, int role);

    /// Set initial confirmed flag
    void        setConfirmed(bool isConfirmed);

    /// Get associated artist item (only valid for genre item).
    CategorizeArtistItem* artistItem() const;

    /// Get associated genres (only valid for artist item).
    const QList<CategorizeArtistItem*> genreItems() const;

    /// Set (child-) genre (only valid for artist item).
    void activateGenre(const QModelIndex& index);

private:
    CategorizeArtistModel*          m_model;
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
