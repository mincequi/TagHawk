#include "Reader.h"

#include <iostream>
#include <sstream>

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

#include <taglib/fileref.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

#include "Collection.h"
#include "Defines.h"
#include "ReaderUtil.h"


using namespace TagLib;

namespace reader
{

Reader::Reader(Collection& database, QObject *parent) :
    QObject(parent),
    m_collection(database),
    m_currentProgress(-1)
{
}

void Reader::read(const QStringList& locations)
{
    QStringList foundFiles;

    for (const auto& location : locations)
    {
        QFileInfo locationInfo(location);

        // Check if location is a file
        if (locationInfo.isFile()) {
            foundFiles << location;
            continue;
        }

        // Check if location is unknown
        if (!locationInfo.isDir()) {
            qDebug() << "Location:" << location.toUtf8().constData() << "is unknown.";
            continue;
        }

        // We have a directory to scan

        // Scan files in current dir
        emit scanningDirectory(location);
        QCoreApplication::processEvents();
        QDirIterator fileIt(location, supportedExtensions, QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
        while (fileIt.hasNext()) {
            foundFiles << fileIt.next();
        }

        QDirIterator dirIt(location, QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable, QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            QString currentDir = dirIt.next();
            emit scanningDirectory(currentDir);
            QCoreApplication::processEvents();
            QDirIterator fileIt(currentDir, supportedExtensions, QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
            while (fileIt.hasNext()) {
                foundFiles << fileIt.next();
            }
        }
    }

    emit scanningDirectory("");
    QCoreApplication::processEvents();
    readTags(foundFiles);
}

void Reader::readTags(const QStringList& files)
{
    emit progress(-1, files.count());
    QCoreApplication::processEvents();

    m_collection.beginWriting();
    int count = 0;
    for (const auto& file : files) {
        emit progress(++count, files.count());
        QCoreApplication::processEvents();

        TagLib::MPEG::File mp3(file.toUtf8().constData(), false);

        const ID3v1::Tag* id3v1Tag = mp3.ID3v1Tag();
        const ID3v2::Tag* id3v2Tag = mp3.ID3v2Tag();
        // Need to use hasId3vXTag method to really obtain existence of id3 tag.
        const bool hasId3v1Tag = mp3.hasID3v1Tag();
        const bool hasId3v2Tag = mp3.hasID3v2Tag();

        // 1. Both tags available
        if (hasId3v1Tag && hasId3v2Tag) {
            // 1.1 Both tags similor -> strip it.
            if (*id3v1Tag == *id3v2Tag ) {
                //qDebug() << "Equal ID3v1 and ID3v2 tags present in file:" << file.toUtf8().constData();
                //std::stringstream sstr;
                //sstr << "id3v1Tag:" << std::endl;
                //sstr << *id3v1Tag << std::endl;
                //sstr << "id3v2Tag:" << std::endl;
                //sstr << *id3v2Tag << std::endl;
                //qDebug() << sstr.str().c_str();
                emit stripId3v1(file);
            // 1.2 id3v1 empty -> strip it.
            } else if (id3v1Tag->isEmpty()) {
                qDebug() << "ID3v1 tag is empty in file:" << file.toUtf8().constData();
                emit stripId3v1(file);
            } else {
                qWarning() << "Unequal ID3v1 and ID3v2 tags present in file:" << file.toUtf8().constData();
                std::stringstream sstr;
                sstr << "id3v1Tag:" << std::endl;
                sstr << *id3v1Tag << std::endl;
                sstr << "id3v2Tag:" << std::endl;
                sstr << *id3v2Tag << std::endl;
                qDebug() << sstr.str().c_str();
            }
        // 2. Only id3v1 available
        } else if (hasId3v1Tag) {
            qWarning() << "Only ID3v1 tag present in file:" << file.toUtf8().constData();
            continue;
        // 3. Only id3v2 available
        } else if (hasId3v2Tag) {
            //qDebug() << "Only ID3v2 tag present in file:" << file.toUtf8().constData();
        // 4. None available
        } else {
            qWarning() << "No tag present in file:" << file.toUtf8().constData();
            continue;
        }

        m_collection.appendEntry(file,
                                 TStringToQString(id3v2Tag->artist()),
                                 TStringToQString(id3v2Tag->album()),
                                 id3v2Tag->track(),
                                 TStringToQString(id3v2Tag->title()),
                                 id3v2Tag->year(),
                                 TStringToQString(id3v2Tag->genre()));
    }
    m_collection.endWriting();

    emit progress(files.count()+1, files.count());
    QCoreApplication::processEvents();
}

} // namespace reader
