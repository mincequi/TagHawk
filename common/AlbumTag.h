#ifndef ALBUMTAG_H
#define ALBUMTAG_H

#include <QString>


struct AlbumTag {
    AlbumTag(const QString& artist  = QString(),
             const QString& album   = QString(),
             std::int16_t year      = 0,
             const QString& genre   = QString());

    QString         artist;
    QString         album;
    std::int16_t    year;
    QString         genre;

    void clear();
    bool isValid();

    /*!
     * Returns true if and only if \other has the same contents as this AlbumTag.
     */
    bool operator==(const AlbumTag &other) const;

    /*!
     * Returns false if and only \other has the same contents as this AlbumTag.
     */
    bool operator!=(const AlbumTag &other) const;
};

#endif // ALBUMTAG_H
