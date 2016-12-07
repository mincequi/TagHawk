#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T09:51:04
#
#-------------------------------------------------

QT       += core gui network xml sql
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TagHawk
TEMPLATE = app


SOURCES += \
    main.cpp\
    MainWindow.cpp \
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
    config/Config.cpp \
    config/Genres.cpp \
    config/Tags.cpp \
    scraper/LastFmScraper.cpp \
    scraper/LastFmCache.cpp \
    lector/Lector.cpp \
    scraper/LastFmUtil.cpp \
    editor/Editor.cpp \
    #gui/SourcesModel.cpp \
    #gui/SourceTreeView.cpp \
    gui/AmbiguousTagsView.cpp \
    gui/CorrectArtistsView.cpp \
    gui/GenrefyArtistsView.cpp \
    gui/ViewFactory.cpp \
    #editor/GenreDelegate.cpp \
    editor/EditorUtil.cpp \
    editor/CorrectArtistsModel.cpp \
    gui/SettingsDialog.cpp \
    lector/CorrectorBase.cpp \
    lector/GenreListModel.cpp \
    gui/SidebarItem.cpp \
    gui/GenreListView.cpp \
    editor/CategorizeArtistsModel.cpp \
    editor/AltCategorizeArtistsModel.cpp \
    collection/JobsModel.cpp \
    collection/Job.cpp

HEADERS  += \
    Defines.h \
    MainWindow.h \
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
    common/Media.h \
    common/Tag.h \
    config/Config.h \
    config/Genres.h \
    config/Tags.h \
    scraper/LastFmScraper.h \
    scraper/LastFmCache.h \
    lector/Lector.h \
    scraper/LastFmUtil.h \
    editor/Editor.h \
    #gui/SourcesModel.h \
    #gui/SourceTreeView.h \
    gui/AmbiguousTagsView.h \
    gui/CorrectArtistsView.h \
    gui/GenrefyArtistsView.h \
    gui/SettingsDialog.h \
    gui/ViewFactory.h \
    #editor/GenreDelegate.h \
    editor/EditorUtil.h \
    editor/EditorDefines.h \
    editor/CorrectArtistsModel.h \
    lector/CorrectorBase.h \
    lector/GenreListModel.h \
    gui/SidebarItem.h \
    gui/GenreListView.h \
    editor/CategorizeArtistsModel.h \
    editor/AltCategorizeArtistsModel.h \
    collection/JobsModel.h \
    collection/Job.h

FORMS    += \
    gui/renameartist.ui \
    gui/tagartist.ui \
    gui/TagArtistDelegate.ui \
    gui/SettingsDialog.ui \
    gui/MainWindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += taglib

unix|win32: LIBS += -llastfm5

DISTFILES +=

RESOURCES += \
    data/icons/icons.qrc
