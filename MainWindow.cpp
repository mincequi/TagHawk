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

#include "categorizeartists/CategorizeArtistsModel.h"
#include "categorizeartists/CategorizeArtistsView.h"
#include "correctartists/CorrectArtistsModel.h"
#include "correctartists/CorrectArtistsView.h"

#include "config/Config.h"
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

    // Gui related events
    connect(&m_collection.reader(), &AbstractReader::scanningDirectory, this, &MainWindow::onReaderCurrentDirChanged);
    connect(&m_collection.reader(), &AbstractReader::progress, this, &MainWindow::onReaderProgressChanged);
    connect(&m_collection,          &Collection::sizeChanged, this, &MainWindow::onCollectionSizeChanged);

    // Internal events
    connect(&m_collection, &Collection::artistAdded, &m_lector, &CorrectorBase::getGenres);

    // Use case related events
    connect(&m_lector, &CorrectorBase::artist, &m_correctArtistModel, &CorrectArtistsModel::setCanonicalName);
    connect(&m_lector, &CorrectorBase::genres, &m_categorizeArtistModel, &CategorizeArtistsModel::setGenres);

    connect(&m_correctArtistModel, &CorrectArtistsModel::artistRenamed, &m_collection, &Collection::renameArtist);

    connect(&m_categorizeArtistModel, &CategorizeArtistsModel::genreBlacklisted, m_lector.blacklistModel(), &GenreListModel::add);
    connect(&m_categorizeArtistModel, &CategorizeArtistsModel::genreWhitelisted, m_lector.whitelistModel(), &GenreListModel::add);
    connect(&m_categorizeArtistModel, &CategorizeArtistsModel::artistCategorized, [this](const QString& artist, const QString& genre, int* rows) {
        m_collection.categorizeArtist(artist, genre, rows);
        auto artistNames = m_correctArtistModel.originalNames(artist);
        for (const auto& artist_ : artistNames) {
            m_collection.categorizeArtist(artist_, genre, rows);
        }
    });

    // When auto tag feature changed its config or white/blacklist have changed, we trigger a pending rescan.
    connect(&Config::instance(), &Config::genresChanged,    this, &MainWindow::setPendingRescan);
    connect(m_lector.blacklistModel(),  &GenreListModel::changed,   this, &MainWindow::setPendingRescan);
    connect(m_lector.whitelistModel(),  &GenreListModel::changed,   this, &MainWindow::setPendingRescan);

    setupCollectionView();
    setupCategorizeArtistsView();
    setupCorrectArtistsView();
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
}

void MainWindow::on_actionClear_triggered(bool /*checked*/)
{
    m_collection.clear();
}

void MainWindow::on_actionSave_triggered(bool /*checked*/)
{
    m_collection.writer().write();
}

void MainWindow::on_actionSettings_triggered(bool /*checked*/)
{
    m_settingsDialog->show();
}

void MainWindow::setupSidebar()
{
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->sidebarWidget->layout()->addItem(spacer);
}

void MainWindow::setupCollectionView()
{
}

void MainWindow::setupCorrectArtistsView()
{
    CorrectArtistsView* v = new CorrectArtistsView(this);
    v->setModel(&m_correctArtistModel);
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->correctArtistButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupCategorizeArtistsView()
{
    CategorizeArtistsView* v = new CategorizeArtistsView(this);
    v->setModel(&m_categorizeArtistModel);
    //v->setModel(testModel());
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->categorizeArtistButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupCorrectAlbumsView()
{
}

void MainWindow::setupDateAlbumsView()
{
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
