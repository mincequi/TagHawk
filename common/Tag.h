#ifndef TAG_H
#define TAG_H

#include <QString>


struct Tag
{
    QString      title;
    QString      artist;
    QString      album;
    QString      comment;
    QString      genre;
    std::int16_t year = 0;
    std::int16_t track = 0;
}

#endif // TAG_H
