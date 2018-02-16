#include "CategorizeArtistView.h"

#include <functional>

#include <QHeaderView>
#include <QMenu>

#include "CategorizeArtistDefines.h"
#include "CategorizeArtistModel.h"


CategorizeArtistView::CategorizeArtistView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowTitle(QObject::tr("Categorize Artists"));

    connect(this, &QAbstractItemView::doubleClicked, this, &CategorizeArtistView::onDoubleClicked);
    connect(this, &QAbstractItemView::customContextMenuRequested, this, &CategorizeArtistView::onContextMenuRequested);
}

CategorizeArtistView::~CategorizeArtistView()
{
}

void CategorizeArtistView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    header()->moveSection(ArtistColumn, GenreColumn);
}

void CategorizeArtistView::onDoubleClicked(const QModelIndex& index)
{
    CategorizeArtistItem* item = static_cast<CategorizeArtistItem*>(index.internalPointer());
    if (!item) {
        return;
    }

    switch (item->type()) {
    case CategorizeArtistItem::Type::Artist:
        if (index.column() != GenreColumn) {
            return;
        }
        edit(index);
        break;
    case CategorizeArtistItem::Type::Genre:
    {
        item->artistItem()->activateGenre(index);
        break;
    }
    case CategorizeArtistItem::Type::Root:
        break;
    }
}

void CategorizeArtistView::onContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = indexAt(pos);
    if (index.column() != GenreColumn) {
        return;
    }

    CategorizeArtistModel* model_ = static_cast<CategorizeArtistModel*>(model());

    QMenu menu;
    QString genre = index.data().toString();
    connect(menu.addAction("Blacklist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistModel::genreBlacklisted, model_, genre));
    connect(menu.addAction("Whitelist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistModel::genreWhitelisted, model_, genre));
    menu.exec(mapToGlobal(pos));
}
