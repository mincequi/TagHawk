#include "GenreListView.h"

#include <functional>
#include <set>

#include <QContextMenuEvent>
#include <QMenu>

#include "lector/GenreListModel.h"


GenreListView::GenreListView(QWidget *parent)
    : QListView(parent)
{
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

GenreListView::~GenreListView()
{
}

#ifndef QT_NO_CONTEXTMENU
void GenreListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    connect(menu.addAction("Remove"), &QAction::triggered, std::bind(&GenreListView::removeSelection, this));
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMEN

void GenreListView::removeSelection()
{
    QModelIndexList selection = selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        return;
    }

    std::set<int> rows;
    for (const auto& index : selection) {
        rows.insert(index.row());
    }

    GenreListModel* model_ = static_cast<GenreListModel*>(model());
    for (auto rit = rows.rbegin(); rit != rows.rend(); ++rit) {
        model_->removeRow(*rit);
    }

    emit model_->changed();
}
