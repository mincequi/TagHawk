#ifndef LASTFMSCRAPER_H
#define LASTFMSCRAPER_H

#include "LastFmCache.h"

#include "lector/CorrectorBase.h"

namespace scraper {
namespace lastfm {

class LastFmScraper : public CorrectorBase
{
    Q_OBJECT
public:
    explicit LastFmScraper(QObject *parent = 0);

    void getGenres(const QString& artist) override;

private slots:
    void onArtistGetTopTags(const QString& artis);

private:
    QString correctArtist(const QString& uncorrected);

    LastFmCache m_cache;
};

} // namespace lastfm
} // namespace scraper

#endif // LASTFMSCRAPER_H
