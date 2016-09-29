#include "CorrectArtistsView.h"

#include <functional>

#include <QMenu>


CorrectArtistsView::CorrectArtistsView(QWidget *parent)
    : QTreeView(parent)
{
    m_model = new QStandardItemModel(this);
    m_model->setHorizontalHeaderLabels( { "Uncorrected", "Corrected", "Confirmed" } );

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setModel(m_model);
    setWindowTitle(QObject::tr("Correct Artists"));

    connect(this, &QAbstractItemView::customContextMenuRequested, this, &CorrectArtistsView::onContextMenuRequested);
}

CorrectArtistsView::~CorrectArtistsView()
{
}

void CorrectArtistsView::correct(const QString& uncorrected, const QString& corrected)
{
    QList<QStandardItem*> row;
    QStandardItem* checkboxItem = new QStandardItem(true);
    checkboxItem->setCheckable(true);
    checkboxItem->setCheckState(Qt::Checked);
    row << new QStandardItem(uncorrected) << new QStandardItem(corrected) << checkboxItem;

    m_model->invisibleRootItem()->appendRow(row);
}

void CorrectArtistsView::onContextMenuRequested(const QPoint& pos)
{
    QMenu menu;
    connect(menu.addAction("Check"), &QAction::triggered, std::bind(&CorrectArtistsView::checkSelection, this, Qt::Checked));
    connect(menu.addAction("Uncheck"), &QAction::triggered, std::bind(&CorrectArtistsView::checkSelection, this, Qt::Unchecked));
    menu.exec(mapToGlobal(pos));
}

void CorrectArtistsView::checkSelection(Qt::CheckState state)
{
    QModelIndexList selection = selectionModel()->selectedRows(2);

    for (const auto& index : selection) {
        m_model->itemFromIndex(index)->setCheckState(state);
    }
}
