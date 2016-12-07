#include "CorrectArtistsView.h"

#include <functional>

#include <QMenu>
#include <QStandardItemModel>


CorrectArtistsView::CorrectArtistsView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowTitle(QObject::tr("Correct Artists"));

    connect(this, &QAbstractItemView::customContextMenuRequested, this, &CorrectArtistsView::onContextMenuRequested);
}

CorrectArtistsView::~CorrectArtistsView()
{
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
        QStandardItemModel* model_ = static_cast<QStandardItemModel*>(model());
        model_->itemFromIndex(index)->setCheckState(state);
    }
}
