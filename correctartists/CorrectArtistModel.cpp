#include "CorrectArtistModel.h"

#include <QDebug>

#include "config/Config.h"

enum Column : int
{
    OriginalColumn = 0,
    CanonicalColumn = 1,
    ConfirmedColumn = 2,
    AffectedFilesColumn = 3
};

CorrectArtistModel::CorrectArtistModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels( { "Original", "Canonical", "Confirmed", "Affected Files" } );

    connect(this, &CorrectArtistModel::dataChanged, [this](const QModelIndex& index_) {
        QString canonical = index_.data(Qt::CheckStateRole).toBool() ? data(index(index_.row(), 1)).toString() : QString();
        int numFiles = 0;
        emit artistRenamed(data(index(index_.row(), 0)).toString(), canonical, &numFiles);
        setData(index(index_.row(), AffectedFilesColumn), numFiles);
    });
}

CorrectArtistModel::~CorrectArtistModel()
{
}

void CorrectArtistModel::setCanonicalName(const QString& original, const QString& canonical)
{
    auto items = findItems(original, Qt::MatchExactly, OriginalColumn);
    if (!items.empty()) {
        qDebug() << "already inserted (original/canonical):" << original << "/" << canonical;
        int numFiles = 0;
        emit artistRenamed(original, canonical, &numFiles);
        auto index_ = items.front()->index();
        setData(index_.sibling(index_.row(), AffectedFilesColumn), numFiles);
        return;
    }

    // For model interface
    QList<QStandardItem*> row;
    QStandardItem* checkboxItem = new QStandardItem();
    checkboxItem->setCheckable(true);
    row << new QStandardItem(original) << new QStandardItem(canonical) << checkboxItem << new QStandardItem(0);
    invisibleRootItem()->appendRow(row);

    checkboxItem->setCheckState(Qt::Checked);
}

QString CorrectArtistModel::canonicalName(const QString& artist) const
{
    for (int row = 0; row < rowCount(); ++row) {
        if (data(index(row, 0)).toString() == artist) {
            return data(index(row, 1)).toString();
        }
    }

    return artist;
}

QStringList CorrectArtistModel::originalNames(const QString& canonical) const
{
    QStringList names;
    auto items = findItems(canonical, Qt::MatchExactly, CanonicalColumn);
    for (const auto item : items) {
        names << item->index().sibling(item->index().row(), OriginalColumn).data().toString();
    }

    return names;
}
