#include "CorrectArtistsModel.h"

#include <QDebug>

#include "config/Config.h"


CorrectArtistsModel::CorrectArtistsModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels( { "Uncorrected", "Corrected", "Confirmed" } );
}

CorrectArtistsModel::~CorrectArtistsModel()
{
}

void CorrectArtistsModel::correct(const QString& uncorrected, const QString& corrected)
{
    QList<QStandardItem*> row;
    QStandardItem* checkboxItem = new QStandardItem(true);
    checkboxItem->setCheckable(true);
    checkboxItem->setCheckState(Qt::Checked);
    row << new QStandardItem(uncorrected) << new QStandardItem(corrected) << checkboxItem;

    invisibleRootItem()->appendRow(row);
}
