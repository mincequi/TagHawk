#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T09:51:04
#
#-------------------------------------------------

QT       += core gui network xml sql
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bagga
TEMPLATE = app


SOURCES += main.cpp\
    Writer.cpp \
    types/AlbumTag.cpp \
    scraper/LastFmScraper.cpp \
    scraper/LastFmCache.cpp \
    Collection.cpp \
    lector/Lector.cpp \
    scraper/LastFmUtil.cpp \
    editor/Editor.cpp \
    common/DatabaseUtil.cpp \
    #gui/SourcesModel.cpp \
    #gui/SourceTreeView.cpp \
    CorrectorBase.cpp \
    gui/sidebaritem.cpp \
    cache/cache.cpp \
    gui/mainwindow.cpp \
    reader/Reader.cpp \
    reader/ReaderUtil.cpp \
    gui/ViewFactory.cpp \
    editor/TagArtistsModel.cpp \
    editor/TagArtistsDelegate.cpp \
    editor/EditorUtil.cpp

HEADERS  += \
    Writer.h \
    Media.h \
    Defines.h \
    types/Cluster.h \
    types/AlbumTag.h \
    scraper/LastFmScraper.h \
    scraper/LastFmCache.h \
    Collection.h \
    lector/Lector.h \
    scraper/LastFmUtil.h \
    editor/Editor.h \
    common/DatabaseUtil.h \
    #gui/SourcesModel.h \
    #gui/SourceTreeView.h \
    CorrectorBase.h \
    gui/sidebaritem.h \
    cache/cache.h \
    gui/mainwindow.h \
    reader/Reader.h \
    reader/ReaderUtil.h \
    gui/ViewFactory.h \
    editor/TagArtistsModel.h \
    editor/TagArtistsDelegate.h \
    editor/EditorUtil.h

FORMS    += \
    gui/renameartist.ui \
    gui/tagartist.ui \
    gui/mainwindow.ui \
    gui/TagArtistDelegate.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += taglib

unix|win32: LIBS += -llastfm5

DISTFILES +=
