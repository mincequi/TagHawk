#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "collection/Collection.h"
#include "editor/Editor.h"
#include "lector/Lector.h"


class SettingsDialog;
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

private slots:
    void onReaderCurrentDirChanged(const QString& directory);
    void onReaderProgressChanged(int value, int maximum);
    void setPendingRescan();
    void onCollectionSizeChanged(int size);
    void onJobsChanged(int count);
    void on_actionAddFolder_triggered(bool checked);
    void on_actionAddFiles_triggered(bool checked);
    void on_actionRescan_triggered(bool checked);
    void on_actionClear_triggered(bool checked);
    void on_actionSave_triggered(bool checked);
    void on_actionSettings_triggered(bool checked);

private:
    void setupCollectionView();
    void setupGenrefyArtistsView();
    void setupCorrectArtistView();
    void setupJobsView();
    void setupAutoTaggerViews();
    void setupSidebar();

    Ui::MainWindow* ui;
    SettingsDialog* m_settingsDialog;
    QProgressBar*   m_progressBar;

    // Top-level app components
    collection::Collection  m_collection;
    lector::Lector          m_lector;
    editor::Editor          m_editor;

    //
    QString m_recentFolder;
};

#endif // MAINWINDOW_H
