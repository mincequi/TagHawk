#include "TagLibWriter.h"

#include <map>

#include <QDebug>
#include <QFileInfo>

#include <taglib/mpegfile.h>

#include "Collection.h"
#include "TagLibWriterUtil.h"

TagLibWriter::TagLibWriter(Collection& collection, QObject *parent) :
    AbstractWriter(parent),
    m_collection(collection)
{
}

void TagLibWriter::write() const
{
    auto entries = m_collection.entries();
    return;

    for (const Collection::Entry& entry : entries) {
        TagLib::MPEG::File file(QFile::encodeName(entry.fileName), false);
        auto tag = file.ID3v2Tag(true);

        bool tagSet = false;
        if (entry.forceWrite) {
            tag->setArtist(QStringToTString(entry.artist));
            tag->setAlbum(QStringToTString(entry.album));
            tag->setTrack(entry.track);
            tag->setTitle(QStringToTString(entry.title));
            tag->setYear(entry.year);
            tag->setGenre(QStringToTString(entry.genre));
            tagSet = true;
        }

        if (!entry.newArtist.isEmpty()) {
            tag->setArtist(QStringToTString(entry.newArtist));
            tagSet = true;
        }
        if (!entry.newAlbum.isEmpty()) {
            tag->setAlbum(QStringToTString(entry.newAlbum));
            tagSet = true;
        }
        if (entry.newTrack > 0) {
            tag->setTrack(entry.newTrack);
            tagSet = true;
        }
        if (!entry.newTitle.isEmpty()) {
            tag->setTitle(QStringToTString(entry.newTitle));
            tagSet = true;
        }
        if (entry.newYear > 0) {
            tag->setYear(entry.newYear);
            tagSet = true;
        }
        if (!entry.newGenre.isEmpty()) {
            tag->setGenre(QStringToTString(entry.newGenre));
            tagSet = true;
        }

        if (tagSet) {
            file.save(TagLib::MPEG::File::ID3v2, entry.stripId3v1);
        } else if (entry.stripId3v1) {
            file.strip(TagLib::MPEG::File::ID3v1);
        } else {
            qDebug() << "no op for file " << entry.fileName;
        }
    }
}
