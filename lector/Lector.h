#ifndef LECTOR_H
#define LECTOR_H

#include <QStringListModel>

#include "CorrectorBase.h"
#include "GenreListModel.h"
#include "config/Genres.h"
#include "scraper/LastFmScraper.h"

namespace lector {

class Lector : public CorrectorBase
{
    Q_OBJECT
public:
    explicit Lector(QObject *parent = 0);
    ~Lector();

    void getGenres(const QString& artist) override;

    GenreListModel* blacklistModel();
    GenreListModel* whitelistModel();

private slots:
    void onConfigChanged();
    void on_scraper_genres(const QString& artist, const QMap<int, QString>& genres);

private:
    bool isBlacklisted(const QString& genre);
    bool isWhitelisted(const QString& genre);
    void spellCheck(QString& genre);

    config::Genres  m_config;

    scraper::lastfm::LastFmScraper   m_scraper;

    GenreListModel m_blacklistModel;
    GenreListModel m_whitelistModel;
};

} // namespace lector

#endif // LECTOR_H
