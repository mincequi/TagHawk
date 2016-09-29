#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Collection.h>

#include <cache/cache.h>
#include <editor/Editor.h>
#include <lector/Lector.h>
#include <reader/Reader.h>
#include <scraper/LastFmScraper.h>


class QProgressBar;

namespace Ui {
class MainWindow;
}

namespace scraper {
namespace lastfm {
class LastFmCache;
}
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void read(const QStringList& locations);

private slots:
    void onScanningDirectory(const QString& directory);
    void onReaderProgress(int value, int maximum);

private:
    void setupTagArtistView();
    void setupCacheViews();
    void setupSidebar();

    Ui::MainWindow* ui;
    QProgressBar*   m_progressBar;

    // Top-level app components
    Collection      m_collection;
    reader::Reader  m_reader;
    lector::Lector  m_lector;
    editor::Editor  m_editor;

    // View relevant components
    Cache               m_cache;
    QVector<QWidget*>   m_cacheWidgets;
};

#endif // MAINWINDOW_H
