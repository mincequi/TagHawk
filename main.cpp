#include "gui/mainwindow.h"
#include <QApplication>
#include <QStatusBar>

#include <iostream>


using namespace scraper::lastfm;

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{file}:%{line}> %{message}");

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QStringList paths;
    paths.push_back(QString(argv[1]));
    w.read(paths);

    return a.exec();
}
