#ifndef LECTOR_H
#define LECTOR_H

#include <CorrectorBase.h>
#include <scraper/LastFmScraper.h>

#include <QSqlDatabase>


namespace lector {

class Lector : public CorrectorBase
{
public:
    explicit Lector(QObject *parent = 0);

    void getGenres(const QString& artist) override;

    scraper::lastfm::LastFmScraper& scraper();

private slots:
    void onScraperGenres(const QString& artist, const QMap<int, QString>& genres);

private:
    void openDb();
    void closeDb();

    bool isWhitelisted(const QString& genre);
    bool isBlacklisted(const QString& genre);
    void spellCheck(QString& genre);

    scraper::lastfm::LastFmScraper   m_scraper;
    QSqlDatabase m_db;
};

} // namespace lector

#endif // LECTOR_H
