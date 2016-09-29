#include "GenrefyArtistsView.h"

#include <functional>

#include <QMenu>


GenrefyArtistsView::GenrefyArtistsView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    //setSelectionMode(QAbstractItemView::ExtendedSelection);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowTitle(QObject::tr("Genrefy Artists"));
    header()->moveSection(2, 0);

    connect(this, &QAbstractItemView::doubleClicked, this, &GenrefyArtistsView::onGenreDoubleClicked);
    connect(this, &QAbstractItemView::customContextMenuRequested, this, &GenrefyArtistsView::onContextMenuRequested);
}

GenrefyArtistsView::~GenrefyArtistsView()
{
}

void GenrefyArtistsView::onGenreDoubleClicked(const QModelIndex& index)
{
    if (index.column() != 0) {
        return;
    }

    int type = index.data(TypeRole).toInt();
    switch (type) {
    case ArtistItem:
        m_genreView->edit(index);
        m_genreModel->item(index.row(), 1)->setText("User");
        m_genreModel->item(index.row(), 3)->setCheckState(Qt::Checked);
        break;
    case GenreItem:
    {
        QString genre = index.data().toString();
        QString weight = index.data(WeightRole).toString();

        QStandardItem*  parent = m_genreModel->itemFromIndex(index.parent());
        parent->setText(genre);
        m_genreModel->item(parent->index().row(), 1)->setText(weight);
        m_genreModel->item(parent->index().row(), 3)->setCheckState(Qt::Checked);
        break;
    }
    default:
        break;
    }
}

void GenrefyArtistsView::onContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = m_genreView->indexAt(pos);

    if (index.column() != 0) {
        return;
    }

    QMenu menu;
    QString genre = index.data().toString();
    connect(menu.addAction("Blacklist \"" + genre + "\""), &QAction::triggered, std::bind(&Editor::genreBlacklisted, this, genre));
    connect(menu.addAction("Whitelist \"" + genre + "\""), &QAction::triggered, std::bind(&Editor::genreWhitelisted, this, genre));
    menu.exec(m_genreView->mapToGlobal(pos));
}
