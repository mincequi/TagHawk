#include "LastFmScraper.h"

#include <functional>

#include <QDebug>
#include <QtNetwork/QNetworkReply>

#include <lastfm5/Artist.h>
#include <lastfm5/Tag.h>
#include <lastfm5/ws.h>

#include "Defines.h"
#include "LastFmUtil.h"


namespace scraper {
namespace lastfm {

LastFmScraper::LastFmScraper(QObject *parent)
    : CorrectorBase(parent)
{
    ::lastfm::ws::ApiKey = apiKey;
    ::lastfm::ws::SharedSecret = sharedSecret;
}

void LastFmScraper::getGenres(const QString& artist)
{
    // We only request from cache, if we found a cannonical artist name
    QString corrected = correctArtist(artist);
    if (!corrected.isEmpty()) {
        const auto tags = m_cache.artist.getTopTags(corrected);
        if (!tags.isEmpty()) {
            emit genres(corrected, tags);
            return;
        }
    }

    auto reply = ::lastfm::Artist(artist).getTopTags();
    auto bind = std::bind(&LastFmScraper::onArtistGetTopTags, this, artist);
    connect(reply, &QNetworkReply::finished, this, bind);
}

void LastFmScraper::onArtistGetTopTags(const QString& uncorrected)
{
    QNetworkReply* reply = static_cast<QNetworkReply*>(sender());

    QString             corrected;
    QMap<int, QString>  tags;

    try {
        if (!artist::getTopTags(reply, tags, corrected)) {
            qWarning() << "No tags available for artist:" << uncorrected;
            return;
        }
    } catch (std::runtime_error& e) {
        qWarning() << e.what();
        return;
    }

    // We set this correction in any case.
    m_cache.artist.setCorrection(uncorrected, corrected);
    if (uncorrected != corrected) {
        emit artist(uncorrected, corrected);
    }

    m_cache.artist.setTopTags(corrected, tags);
    emit genres(corrected, tags);
}

const LastFmCache& LastFmScraper::cache() const
{
    return m_cache;
}

QString LastFmScraper::correctArtist(const QString& uncorrected)
{
    QString corrected = m_cache.artist.getCorrection(uncorrected);
    if (!corrected.isEmpty() && corrected != uncorrected) {
        emit artist(uncorrected, corrected);
    }
    return corrected;
}

} // namespace lastfm
} // namespace scraper
