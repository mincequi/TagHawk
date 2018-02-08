#ifndef CATEGORIZEARTISTSMODEL_H
#define CATEGORIZEARTISTSMODEL_H

#include <QAbstractItemModel>

#include "CategorizeArtistsItem.h"
#include "config/Genres.h"

class CategorizeArtistsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CategorizeArtistsModel(QObject *parent = 0);
    virtual ~CategorizeArtistsModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

public slots:
    void setGenres(const QString& artist, const QMap<int, QString>& genres);

signals:
    void genreBlacklisted(const QString& genre);
    void genreWhitelisted(const QString& genre);
    void artistCategorized(const QString& artist, const QString& genre, int* rows);

private:
    CategorizeArtistItem* find(const QString& artist);

    void onConfigChanged();

    config::Genres                  m_config;
    CategorizeArtistItem            m_rootItem;
    QList<CategorizeArtistItem*>    m_artistItems;
};

#endif // CATEGORIZEARTISTSMODEL_H
