#include "CategorizeArtistsView.h"

#include <functional>

#include <QHeaderView>
#include <QMenu>

#include "CategorizeArtistsDefines.h"
#include "CategorizeArtistsModel.h"


CategorizeArtistsView::CategorizeArtistsView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowTitle(QObject::tr("Categorize Artists"));

    connect(this, &QAbstractItemView::doubleClicked, this, &CategorizeArtistsView::onDoubleClicked);
    connect(this, &QAbstractItemView::customContextMenuRequested, this, &CategorizeArtistsView::onContextMenuRequested);
}

CategorizeArtistsView::~CategorizeArtistsView()
{
}

void CategorizeArtistsView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    header()->moveSection(ArtistColumn, GenreColumn);
}

void CategorizeArtistsView::onDoubleClicked(const QModelIndex& index)
{
    if (index.column() != GenreColumn) {
        return;
    }

    CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());
    switch (item->type()) {
    case CategorizeArtistItem::Type::Artist:
        edit(index);
        break;
    case CategorizeArtistItem::Type::Genre:
    {
        item->artistItem()->activateGenre(item);
        QModelIndex index2 = index.parent();
        model()->dataChanged(index2, index2.sibling(index2.row(), ConfirmedColumn));
        break;
    }
    case CategorizeArtistItem::Type::Root:
        break;
    }
}

void CategorizeArtistsView::onContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = indexAt(pos);
    if (index.column() != GenreColumn) {
        return;
    }

    CategorizeArtistsModel* model_ = static_cast<CategorizeArtistsModel*>(model());

    QMenu menu;
    QString genre = index.data().toString();
    connect(menu.addAction("Blacklist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistsModel::genreBlacklisted, model_, genre));
    connect(menu.addAction("Whitelist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistsModel::genreWhitelisted, model_, genre));
    menu.exec(mapToGlobal(pos));
}
