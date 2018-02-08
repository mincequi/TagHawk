#include "MainWindow.h"
#include <QApplication>
#include <QStatusBar>

#include <iostream>


using namespace scraper::lastfm;

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{file}:%{line}> %{message}");

    QApplication a(argc, argv);
    QApplication::setOrganizationName("TagHawk");
    QApplication::setOrganizationDomain("taghawk.org");
    QApplication::setApplicationName("TagHawk");

    MainWindow w;
    w.show();

    return a.exec();
}
