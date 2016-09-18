#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <common/DatabaseUtil.h>
#include <editor/TagArtistsDelegate.h>

#include <QMapIterator>
#include <QProgressBar>
#include <QSqlQueryModel>
#include <QTableView>

#include <functional>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_progressBar(new QProgressBar(this)),
    m_reader(m_collection)
{
    ui->setupUi(this);
    m_progressBar->setRange(0, 100);
    m_progressBar->setFormat("Reading file %v/%m");

    QObject::connect(&m_reader, &reader::Reader::scanningDirectory, this, &MainWindow::onScanningDirectory);
    QObject::connect(&m_reader, &reader::Reader::progress, this, &MainWindow::onReaderProgress);

    QObject::connect(&m_collection, &Collection::artistAdded, &m_lector, &CorrectorBase::getGenres);
    QObject::connect(&m_lector, &CorrectorBase::artist, &m_editor, &editor::Editor::correctArtist);
    QObject::connect(&m_lector, &CorrectorBase::genres, &m_editor, &editor::Editor::setGenres);

    setupTagArtistView();
    setupCacheViews();
    setupSidebar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read(const QStringList& locations)
{
    m_reader.read(locations);
}

void MainWindow::onScanningDirectory(const QString& directory)
{
    if (directory.isEmpty()) {
        ui->statusBar->clearMessage();
        return;
    }

    ui->statusBar->showMessage("Scanning folder: " + directory);
}

void MainWindow::onReaderProgress(int value, int maximum)
{
    m_progressBar->setMaximum(maximum);

    if (value < 0) {
        ui->statusBar->addWidget(m_progressBar);
        m_progressBar->setValue(0);
    } else if (value > maximum) {
        ui->statusBar->removeWidget(m_progressBar);
    } else {
        m_progressBar->setValue(value);
    }
}

void MainWindow::setupTagArtistView()
{
    QTableView* v = new QTableView(this);
    v->setModel(m_editor.genreModel());
    v->setItemDelegate(new TagArtistsDelegate(v));
    ui->stackedWidget->addWidget(v);

    auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
    connect(ui->tagArtistButton, &QAbstractButton::pressed, bind);
}

void MainWindow::setupCacheViews()
{
    // Setup Cache Views
    for (const auto& table : m_cache.tables()) {
        // Create a radio button for each cache table
        QRadioButton* b = new QRadioButton(this);
        b->setText(table);
        ui->sidebarWidget->layout()->addWidget(b);

        // Create a model for each cache table
        QSqlQueryModel* m = new QSqlQueryModel(this);
        QString s("SELECT * FROM :table_name");
        s.replace(":table_name", table);
        m->setQuery(s, ::database::openCache());

        // Create a view for each cache table
        QTableView* v = new QTableView(this);
        v->setModel(m);
        ui->stackedWidget->addWidget(v);

        // Bring view to front when appropriate button is clicked
        auto bind = std::bind(&QStackedWidget::setCurrentWidget, ui->stackedWidget, v);
        connect(b, &QAbstractButton::pressed, bind);
    }
}

void MainWindow::setupSidebar()
{
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->sidebarWidget->layout()->addItem(spacer);
}
