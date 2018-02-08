#include "MainWindow.h"

#include <functional>

#include <QDebug>
#include <QFileDialog>
#include <QListView>
#include <QProgressBar>
#include <QSqlQueryModel>
#include <QTableView>

#include <common/DatabaseUtil.h>

#include "ui_MainWindow.h"

#include "collection/JobsModel.h"
#include "config/Config.h"
#include "editor/CategorizeArtistsModel.h"
#include "editor/CorrectArtistsModel.h"
#include "gui/CorrectArtistsView.h"
#include "gui/GenrefyArtistsView.h"
#include "gui/GenreListView.h"
#include "gui/SettingsDialog.h"

#include "lector/GenreListModel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settingsDialog(new SettingsDialog(this)),
    m_progressBar(new QProgressBar(this))
{
    ui->setupUi(this);
    m_progressBar->hide();
    m_progressBar->setFormat("Reading file %v/%m");

    connect(&m_collection.reader(), &collection::AbstractReader::scanningDirectory, this, &MainWindow::onReaderCurrentDirChanged);
    connect(&m_collection.reader(), &collection::AbstractReader::progress, this, &MainWindow::onReaderProgressChanged);

    connect(&m_collection, &collection::Collection::sizeChanged, this, &MainWindow::onCollectionSizeChanged);
    connect(&m_collection, &collection::Collection::artistAdded, &m_lector, &CorrectorBase::getGenres);
    connect(m_collection.jobsModel(), &JobsModel::jobsChanged, this, &MainWindow::onJobsChanged);

    connect(&m_lector, &CorrectorBase::artist, m_editor.correctArtistsModel(), &CorrectArtistsModel::correct);
    connect(&m_lector, &CorrectorBase::genres, m_editor.categorizeArtistsModel(), &CategorizeArtistsModel::setGenres);

    connect(m_editor.categorizeArtistsModel(), &CategorizeArtistsModel::genreBlacklisted, m_lector.blacklistModel(), &GenreListModel::add);
    connect(m_editor.categorizeArtistsModel(), &CategorizeArtistsModel::genreWhitelisted, m_lector.whitelistModel(), &GenreListModel::add);


    // When auto tag feature changed its config or white/blacklist have changed, we trigger a pending rescan.
    connect(&Config::instance(), &Config::genresChanged,    this, &MainWindow::setPendingRescan);
    connect(m_lector.blacklistModel(),  &GenreListModel::changed,   this, &MainWindow::setPendingRescan);
    connect(m_lector.whitelistModel(),  &GenreListModel::changed,   this, &MainWindow::setPendingRescan);

    setupCollectionView();
    setupGenrefyArtistsView();
    setupCorrectArtistView();
    setupJobsView();
    setupAutoTaggerViews();
    setupSidebar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReaderCurrentDirChanged(const QString& dir)
{
    if (dir.isEmpty()) {
        ui->statusBar->clearMessage();
        return;
    }

    ui->statusBar->showMessage("Scanning folder: " + dir);
}

void MainWindow::onReaderProgressChanged(int value, int maximum)
{
    m_progressBar->setMaximum(maximum);
    m_progressBar->setValue(value);

    if (value == 0) {
        ui->statusBar->addWidget(m_progressBar);
        ui->statusBar->show();
    } else if (value > maximum) {
        ui->statusBar->hide();
        ui->statusBar->removeWidget(m_progressBar);
    }
}

void MainWindow::setPendingRescan()
{
    ui->actionRescan->setEnabled(!m_collection.isEmpty());
}

void MainWindow::onCollectionSizeChanged(int size)
{
    ui->actionClear->setEnabled(size > 0);
}

void MainWindow::onJobsChanged(int count)
{
    ui->actionSave->setEnabled(count > 0);
}

void MainWindow::on_actionAddFolder_triggered(bool /*checked*/)
{
    m_recentFolder = QFileDialog::getExistingDirectory(this, tr("Add Folder"), m_recentFolder);

    if (m_recentFolder.isEmpty()) {
        return;
    }

    m_collection.reader().readFolder(m_recentFolder);
}

void MainWindow::on_actionAddFiles_triggered(bool /*checked*/)
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Add Folder"), m_recentFolder, "Audio Files (*.mp3)");

    if (files.isEmpty()) {
        return;
    }

    QFileInfo fileInfo(files.first());
    m_recentFolder = fileInfo.dir().absolutePath();
    m_collection.reader().readFiles(files);
}

void MainWindow::on_actionRescan_triggered(bool /*checked*/)
{
    ui->actionRescan->setEnabled(false);
    m_editor.clear();
    m_collection.rescan();
}

void MainWindow::on_actionClear_triggered(bool /*checked*/)
{
    m_editor.clear();
    m_collection.clear();
}

//void MainWindow::updateJobs()
//{
//    auto genres = m_editor.categorizeArtistsModel()->genres();
//
//    for (auto it = genres.begin(); it != genres.end(); ++it) {
//        auto inconsistencies = m_collection.selectGenreInconsistencies(it.key(), it.value());
//        for (const auto& genre : inconsistencies) {
//            auto files = m_collection.selectFiles(it.key(), genre);
//            for (auto& file : files) {
//                tagMap[file].setGenre(job.value().toString().toStdWString());
//            }
//        }
//        break;
//    }
//
//
//    m_collection.selectGenreInconsistencies()
//
//    m_collection.writer().write(jobs);
//}

void MainWindow::on_actionSave_triggered(bool /*checked*/)
{
    auto genres = m_editor.categorizeArtistsModel()->genres();

    //for (auto it = genres.begin(); it != genres.end(); ++it) {
    //    auto inconsistencies = m_collection.selectGenreInconsistencies(it.key(), it.value());
    //    for (const auto& genre : inconsistencies) {
    //        auto files = m_collection.selectFiles(it.key(), genre);
    //        for (auto& file : files) {
    //            tagMap[file].setGenre(job.value().toString().toStdWString());
    //        }
    //    }
    //    break;
    //}
    //
    //
    //m_collection.selectGenreInconsistencies()
    //
    //m_collection.writer().write(jobs);
}

void MainWindow::on_actionSettings_triggered(bool /*checked*/)
{
    m_settingsDialog->show();
}

void MainWindow::setupCollectionView()
{
}

void MainWindow::setupCorrectArtistView()
{
    CorrectArtistsView* v = new CorrectArtistsView(this);
    v->setModel(m_editor.correctArtistsModel());
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->correctArtistButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupGenrefyArtistsView()
{
    GenrefyArtistsView* v = new GenrefyArtistsView(this);
    v->setModel(m_editor.categorizeArtistsModel());
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->tagArtistButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupJobsView()
{
    QTreeView* v = new QTreeView(this);
    v->setModel(m_collection.jobsModel());
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->jobsButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupAutoTaggerViews()
{
    {
        QListView* v = new GenreListView(this);
        v->setModel(m_lector.blacklistModel());
        ui->stackedWidget->addWidget(v);
        auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
        connect(ui->blacklistButton, &QAbstractButton::pressed, bind);
    }

    {
        QListView* v = new GenreListView(this);
        v->setModel(m_lector.whitelistModel());
        ui->stackedWidget->addWidget(v);
        auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
        connect(ui->whitelistButton, &QAbstractButton::pressed, bind);
    }
}

void MainWindow::setupSidebar()
{
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->sidebarWidget->layout()->addItem(spacer);
}
