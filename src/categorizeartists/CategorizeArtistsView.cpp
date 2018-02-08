#include "GenrefyArtistsView.h"

#include <functional>

#include <QHeaderView>
#include <QMenu>

#include <editor/EditorDefines.h>
#include <editor/CategorizeArtistsModel.h>


GenrefyArtistsView::GenrefyArtistsView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowTitle(QObject::tr("Genrefy Artists"));

    connect(this, &QAbstractItemView::doubleClicked, this, &GenrefyArtistsView::onGenreDoubleClicked);
    connect(this, &QAbstractItemView::customContextMenuRequested, this, &GenrefyArtistsView::onContextMenuRequested);
}

GenrefyArtistsView::~GenrefyArtistsView()
{
}

void GenrefyArtistsView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    header()->moveSection(2, 0);
}

void GenrefyArtistsView::onGenreDoubleClicked(const QModelIndex& index)
{
    if (index.column() != 0) {
        return;
    }

    const QStandardItemModel* standardItemModel = static_cast<const QStandardItemModel*>(index.model());
    int type = index.data(CategorizeArtistsModel::TypeRole).toInt();
    switch (type) {
    case CategorizeArtistsModel::ArtistItem:
        edit(index);
        standardItemModel->item(index.row(), 1)->setText("User");
        standardItemModel->item(index.row(), 3)->setCheckState(Qt::Checked);
        break;
    case CategorizeArtistsModel::GenreItem:
    {
        QString genre = index.data().toString();
        QString weight = index.data(CategorizeArtistsModel::WeightRole).toString();
        QStandardItem*  parent = standardItemModel->itemFromIndex(index.parent());
        parent->setText(genre);
        standardItemModel->item(parent->index().row(), 1)->setText(weight);
        standardItemModel->item(parent->index().row(), 3)->setCheckState(Qt::Checked);
        break;
    }
    default:
        break;
    }
}

void GenrefyArtistsView::onContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = indexAt(pos);
    if (index.column() != 0) {
        return;
    }

    CategorizeArtistsModel* model_ = static_cast<CategorizeArtistsModel*>(model());

    QMenu menu;
    QString genre = index.data().toString();
    connect(menu.addAction("Blacklist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistsModel::genreBlacklisted, model_, genre));
    connect(menu.addAction("Whitelist \"" + genre + "\""), &QAction::triggered, std::bind(&CategorizeArtistsModel::genreWhitelisted, model_, genre));
    menu.exec(mapToGlobal(pos));
}
