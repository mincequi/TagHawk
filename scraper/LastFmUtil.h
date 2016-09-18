#ifndef UTIL_H
#define UTIL_H

#include <QMap>
#include <QString>


class QNetworkReply;

namespace scraper {
namespace lastfm {
namespace artist {

bool getTopTags(QNetworkReply* r, QMap<int, QString>& tags, QString& correctedArtist);

} // namespace artist
} // namespace lastfm
} // namespace scraper

#endif // UTIL_H
