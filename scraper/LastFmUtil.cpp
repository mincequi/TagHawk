#include "LastFmUtil.h"

#include <lastfm5/XmlQuery.h>

namespace scraper {
namespace lastfm {
namespace artist {

bool getTopTags(QNetworkReply* r, QMap<int, QString>& tags, QString& correctedArtist)
{
    ::lastfm::XmlQuery lfm;

    if (!lfm.parse(r)) {
        qDebug() << lfm.parseError().message() << lfm.parseError().enumValue();
        return false;
    }
    // check for corrected artist name
    correctedArtist = lfm["toptags"].attribute("artist");
    // parse tags
    foreach (::lastfm::XmlQuery xq, lfm.children("tag")) {
        tags.insertMulti(xq["count"].text().toInt(), xq["name"].text().toLower());
    }

    return (!correctedArtist.isEmpty() && !tags.isEmpty());
}

} // namespace artist
} // namespace lastfm
} // namespace scraper
