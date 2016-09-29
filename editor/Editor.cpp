#include "Editor.h"

#include <functional>

#include <QDebug>
#include <QHeaderView>
#include <QMenu>
#include <QStandardItemModel>
#include <QTreeView>

#include "CorrectArtistsView.h"
#include "EditorDefines.h"
#include "EditorUtil.h"


namespace editor {

Editor::Editor(QObject *parent)
    : QObject(parent),
      m_genreModel(nullptr),
      m_genreView(nullptr),
      m_ambiguousTagsView(nullptr),
      m_correctArtistsView(nullptr)
{
    setupGenreModel();
    //setupGenreSampleData();
}

void Editor::clear()
{
}

void Editor::save()
{
}

QWidget* Editor::createGenrefyArtistsView(QWidget* parent)
{
    if (m_genreView) {
        return m_genreView;
    }

    m_genreView = new QTreeView(parent);
    m_genreView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_genreView->setSelectionMode(QAbstractItemView::NoSelection);
    m_genreView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_genreView->setModel(m_genreModel);
    m_genreView->setWindowTitle(QObject::tr("Tag Artists"));
    m_genreView->header()->moveSection(2, 0);

    connect(m_genreView, &QAbstractItemView::doubleClicked, this, &Editor::onGenreDoubleClicked);
    connect(m_genreView, &QAbstractItemView::customContextMenuRequested, this, &Editor::onContextMenuRequested);

    return m_genreView;
}

QWidget* Editor::createAmbiguousTagsView(QWidget* parent)
{
    if (m_ambiguousTagsView) {
        return m_ambiguousTagsView;
    }

    return m_ambiguousTagsView;
}

QWidget* Editor::createCorrectArtistsView(QWidget* parent)
{
    if (m_correctArtistsView) {
        return m_correctArtistsView;
    }

    m_correctArtistsView = new CorrectArtistsView(parent);

    return m_correctArtistsView;
}

void Editor::correctArtist(const QString& misspelled, const QString& corrected)
{
    if (m_correctArtistsView) {
        m_correctArtistsView->correct(misspelled, corrected);
    }
}

void Editor::correctAlbum(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum)
{
}

void Editor::setGenres(const QString& artist, const QMap<int, QString>& genres)
{
    qDebug() << "Genres for artist" << artist << ":" << genres;

    // 1. Find existing entry

    // 1.1 If exists, modify it

    // 1.2 if not append a new line
    m_genreModel->invisibleRootItem()->appendRow(prepareRow(artist, genres));
}

void Editor::setYear(const QString& artist, const QString& album, const QString& year)
{
}

void Editor::setupGenreModel()
{
    m_genreModel = new QStandardItemModel(this);
    m_genreModel->setHorizontalHeaderLabels( { "Genre", "Weight", "Artist", "Confirmed" } );
}

void Editor::setupGenreSampleData()
{
    QMap<int, QString> genres1;
    genres1[100] = "Death Metal";
    genres1[90] = "Black Metal";
    genres1[80] = "Heavy Metal";

    QMap<int, QString> genres2;
    genres2[100] = "Post-Rock";
    genres2[90] = "Indie";
    genres2[80] = "Alternative";
    genres2[50] = "Icelandic";

    QMap<int, QString> genres3;
    genres3[100] = "Idm";

    QStandardItem* rootItem = m_genreModel->invisibleRootItem();
    rootItem->appendRow(prepareRow("Behemoth", genres1));
    rootItem->appendRow(prepareRow("Sigur Ros", genres2));
    rootItem->appendRow(prepareRow("Autechre", genres3));
}

void Editor::onGenreDoubleClicked(const QModelIndex& index)
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

void Editor::onContextMenuRequested(const QPoint& pos)
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

} // namespace editor
