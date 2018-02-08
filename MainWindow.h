#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "categorizeartists/CategorizeArtistsModel.h"
#include "correctartists/CorrectArtistsModel.h"
#include "correctalbums/CorrectAlbumsModel.h"
#include "datealbums/DateAlbumsModel.h"

#include "collection/Collection.h"
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

    // Handle GUI/Action events
    void on_actionAddFolder_triggered(bool checked);
    void on_actionAddFiles_triggered(bool checked);
    void on_actionRescan_triggered(bool checked);
    void on_actionClear_triggered(bool checked);
    void on_actionSave_triggered(bool checked);
    void on_actionSettings_triggered(bool checked);

private:
    void setupSidebar();
    void setupCollectionView();

    void setupCorrectArtistsView();
    void setupCategorizeArtistsView();
    void setupCorrectAlbumsView();
    void setupDateAlbumsView();

    void setupAutoTaggerViews();

    // Ui elements
    Ui::MainWindow* ui;
    SettingsDialog* m_settingsDialog;
    QProgressBar*   m_progressBar;

    // basic app components
    Collection      m_collection;
    lector::Lector  m_lector;

    // use case components
    CorrectArtistsModel     m_correctArtistModel;
    CategorizeArtistsModel  m_categorizeArtistModel;
    CorrectAlbumsModel      m_correctAlbumsModel;
    DateAlbumsModel         m_dateAlbumsModel;

    //
    QString m_recentFolder;
};

#endif // MAINWINDOW_H
