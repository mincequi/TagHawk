#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T09:51:04
#
#-------------------------------------------------

QT      += core gui network xml sql
CONFIG  += c++11

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Werror

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TagHawk
TEMPLATE = app

INCLUDEPATH += src

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    correctalbums/CorrectAlbumsModel.cpp \
    datealbums/DateAlbumsModel.cpp \
    cache/Cache.cpp \
    collection/AbstractReader.cpp \
    collection/AbstractWriter.cpp \
    collection/Collection.cpp \
    collection/TagLibReader.cpp \
    collection/TagLibReaderUtil.cpp \
    collection/TagLibWriter.cpp \
    collection/TagLibWriterUtil.cpp \
    common/AlbumTag.cpp \
    common/DatabaseUtil.cpp \
    common/Defines.cpp \
    config/Config.cpp \
    config/Genres.cpp \
    config/Tags.cpp \
    scraper/LastFmScraper.cpp \
    scraper/LastFmCache.cpp \
    lector/Lector.cpp \
    scraper/LastFmUtil.cpp \
    #gui/SourcesModel.cpp \
    #gui/SourceTreeView.cpp \
    gui/AmbiguousTagsView.cpp \
    gui/ViewFactory.cpp \
    gui/SettingsDialog.cpp \
    lector/CorrectorBase.cpp \
    lector/GenreListModel.cpp \
    gui/SidebarItem.cpp \
    gui/GenreListView.cpp \
    categorizeartists/CategorizeArtistItem.cpp \
    categorizeartists/CategorizeArtistModel.cpp \
    categorizeartists/CategorizeArtistView.cpp \
    correctartists/CorrectArtistModel.cpp \
    correctartists/CorrectArtistView.cpp

HEADERS  += \
    MainWindow.h \
    common/Defines.h \
    correctalbums/CorrectAlbumsModel.h \
    datealbums/DateAlbumsModel.h \
    Defines.h \
    cache/Cache.h \
    collection/AbstractReader.h \
    collection/AbstractWriter.h \
    collection/Collection.h \
    collection/TagLibReader.h \
    collection/TagLibReaderUtil.h \
    collection/TagLibWriter.h \
    collection/TagLibWriterUtil.h \
    common/AlbumTag.h \
    common/Cluster.h \
    common/DatabaseUtil.h \
    common/Tag.h \
    config/Config.h \
    config/Genres.h \
    config/Tags.h \
    scraper/LastFmScraper.h \
    scraper/LastFmCache.h \
    lector/Lector.h \
    scraper/LastFmUtil.h \
    #gui/SourcesModel.h \
    #gui/SourceTreeView.h \
    gui/AmbiguousTagsView.h \
    gui/SettingsDialog.h \
    gui/ViewFactory.h \
    lector/CorrectorBase.h \
    lector/GenreListModel.h \
    gui/SidebarItem.h \
    gui/GenreListView.h \
    categorizeartists/CategorizeArtistDefines.h \
    categorizeartists/CategorizeArtistItem.h \
    categorizeartists/CategorizeArtistModel.h \
    categorizeartists/CategorizeArtistView.h \
    correctartists/CorrectArtistModel.h \
    correctartists/CorrectArtistView.h

FORMS    += \
    gui/SettingsDialog.ui \
    gui/MainWindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += taglib

unix|win32: LIBS += -llastfm5

DISTFILES +=

RESOURCES += \
    data/icons/icons.qrc
