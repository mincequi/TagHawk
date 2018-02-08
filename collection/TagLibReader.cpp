#include "TagLibReader.h"

#include <iostream>
#include <sstream>

#include <QAbstractButton>
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
#include "TagLibReaderUtil.h"

using namespace TagLib;

TagLibReader::TagLibReader(Collection& collection, QObject *parent) :
    AbstractReader(parent),
    m_collection(collection)
{
}

void TagLibReader::readFolder(const QString& folder)
{
    QStringList foundFiles;
    QFileInfo locationInfo(folder);

    // Check if location is unknown
    if (!locationInfo.isDir()) {
        qWarning() << "Location:" << folder.toUtf8().constData() << "is unknown.";
        return;
    }

    // Scan files in current dir
    QStringList folderName = folder.split('/', QString::SkipEmptyParts);
    emit scanningDirectory(folderName.last());
    QCoreApplication::processEvents();
    QDirIterator fileIt(folder, supportedExtensions, QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    while (fileIt.hasNext()) {
        foundFiles << fileIt.next();
    }

    QDirIterator dirIt(folder, QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable, QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        QString currentDir = dirIt.next();
        QString relativeDir = currentDir;
        emit scanningDirectory(relativeDir.remove(folder).mid(1));
        QCoreApplication::processEvents();
        QDirIterator fileIt(currentDir, supportedExtensions, QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
        while (fileIt.hasNext()) {
            foundFiles << fileIt.next();
        }
    }

    emit scanningDirectory("");
    QCoreApplication::processEvents();
    readFiles(foundFiles);
}

void TagLibReader::readFiles(const QStringList& files)
{
    emit progress(0, files.count());
    QCoreApplication::processEvents();

    m_collection.beginWriting();
    int count = 0;
    for (const auto& file : files) {
        emit progress(++count, files.count());
        QCoreApplication::processEvents();

        TagLib::MPEG::File mp3(QFile::encodeName(file), false);

        const ID3v1::Tag* id3v1Tag = mp3.ID3v1Tag();
        const ID3v2::Tag* id3v2Tag = mp3.ID3v2Tag();
        // Need to use hasId3vXTag method to really obtain existence of id3 tag.
        const bool hasId3v1Tag = mp3.hasID3v1Tag();
        const bool hasId3v2Tag = mp3.hasID3v2Tag();
        bool stripId3v1 = false;

        // 1. Both tags available
        if (hasId3v1Tag && hasId3v2Tag) {
            // 1.1 Both tags similar or id3v1 empty -> strip it.
            if ((*id3v1Tag == *id3v2Tag) || (id3v1Tag->isEmpty())) {
                stripId3v1 = true;
            } else {
                qWarning() << "Unequal ID3v1 and ID3v2 tags present in file:" << file.toUtf8().constData();
                std::stringstream sstr;
                sstr << "id3v1Tag:" << std::endl;
                sstr << *id3v1Tag << std::endl;
                sstr << "id3v2Tag:" << std::endl;
                sstr << *id3v2Tag << std::endl;
                qDebug() << sstr.str().c_str();
                emit ambiguousTagsFound(file);
            }
        // 2. Only id3v1 available
        } else if (hasId3v1Tag) {
            qWarning() << "Only ID3v1 tag present in file:" << file.toUtf8().constData();
            m_collection.appendEntry(file,
                                     TStringToQString(id3v1Tag->artist()),
                                     TStringToQString(id3v1Tag->album()),
                                     id3v1Tag->track(),
                                     TStringToQString(id3v1Tag->title()),
                                     id3v1Tag->year(),
                                     TStringToQString(id3v1Tag->genre()),
                                     true,
                                     true);
            continue;
        // 3. Only id3v2 available
        } else if (hasId3v2Tag) {
            //qDebug() << "Only ID3v2 tag present in file:" << file.toUtf8().constData();
        // 4. None available
        } else {
            qWarning() << "No tag present in file:" << file.toUtf8().constData();
            emit noTagsFound(file);
            continue;
        }

        m_collection.appendEntry(file,
                                 TStringToQString(id3v2Tag->artist()),
                                 TStringToQString(id3v2Tag->album()),
                                 id3v2Tag->track(),
                                 TStringToQString(id3v2Tag->title()),
                                 id3v2Tag->year(),
                                 TStringToQString(id3v2Tag->genre()),
                                 stripId3v1,
                                 false);
    }
    m_collection.endWriting();

    emit progress(files.count()+1, files.count());
    QCoreApplication::processEvents();
}
