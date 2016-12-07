#include "CategorizeArtistsModel.h"

#include <QDebug>

#include "config/Config.h"


CategorizeArtistsModel::CategorizeArtistsModel(QObject *parent)
    : QStandardItemModel(parent),
      m_config(Config::instance().genres())
{
    setHorizontalHeaderLabels( { "Genre", "Weight", "Artist", "Confirmed" } );

    connect(&Config::instance(), &Config::genresChanged, this, &CategorizeArtistsModel::onConfigChanged);
}

CategorizeArtistsModel::~CategorizeArtistsModel()
{
}

QMap<QString, QString> CategorizeArtistsModel::genres() const
{
    QMap<QString, QString> genres;

    for (int row = 0; row < rowCount(); ++row) {
        if (item(row, 3)->checkState() == Qt::Unchecked) {
            continue;
        }

        genres[item(row, 2)->text()] = item(row, 0)->text();
    }

    return genres;
}

void CategorizeArtistsModel::setGenres(const QString& artist, const QMap<int, QString>& genres)
{
    qDebug() << "Genres for artist" << artist << ":" << genres;

    // 1. Add new row if it does not exist
    QList<QStandardItem*> items = findItems(artist, Qt::MatchExactly, 2);
    int row = 0;
    if (items.isEmpty()) {
        appendRow(QList<QStandardItem*> { new QStandardItem(), new QStandardItem(), new QStandardItem(artist), new QStandardItem() } );
        row = rowCount()-1;
    } else {
        row = items.first()->row();
    }

    // 2. Set items children count
    item(row, 0)->setRowCount(genres.size() > 1 ? genres.size() : 0);

    // 3.1 No genres
    if (genres.isEmpty()) {
        return;
    }

    // 3.2 Set first genre
    item(row, 0)->setText(genres.last());
    item(row, 0)->setData(ArtistItem, TypeRole);
    item(row, 0)->setData(QString::number(genres.lastKey()), WeightRole);
    item(row, 1)->setText(QString::number(genres.lastKey()));
    item(row, 3)->setCheckable(true);
    item(row, 3)->setCheckState(genres.lastKey() >= m_config.whitelistWeight ? Qt::Checked : Qt::Unchecked);

    // 3.3 More than one genre provided, add children
    if (genres.size() <= 1) {
        return;
    }
    QMapIterator<int, QString> it(genres);
    it.toBack();
    int childRow = 0;
    while (it.hasPrevious()) {
        it.previous();

        auto item_ = item(row, 0);
        if (!item_->child(childRow, 0)) {
            item_->setChild(childRow, 0, new QStandardItem());
            item_->setChild(childRow, 1, new QStandardItem());
        }
        item_->child(childRow, 0)->setText(it.value());
        item_->child(childRow, 0)->setData(GenreItem, TypeRole);
        item_->child(childRow, 0)->setData(QString::number(it.key()), WeightRole);
        item_->child(childRow, 1)->setText(QString::number(it.key()));

        ++childRow;
    }
}

void CategorizeArtistsModel::onConfigChanged()
{
    m_config = Config::instance().genres();
}
