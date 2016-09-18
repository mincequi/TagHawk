#include "Lector.h"

#include <QDebug>
#include <QRegExp>
#include <QStandardPaths>

#include "Defines.h"
#include "common/DatabaseUtil.h"


namespace lector {

Lector::Lector(QObject *parent)
    : CorrectorBase(parent),
      m_scraper(parent),
      m_db(::database::openConfig())
{
    connect(&m_scraper, &CorrectorBase::artist, this, &CorrectorBase::artist);
    connect(&m_scraper, &CorrectorBase::album, this, &CorrectorBase::album);
    connect(&m_scraper, &CorrectorBase::genres, this, &Lector::onScraperGenres);
    connect(&m_scraper, &CorrectorBase::year, this, &CorrectorBase::year);
}

void Lector::getGenres(const QString& artist)
{
    m_scraper.getGenres(artist);
}

scraper::lastfm::LastFmScraper& Lector::scraper()
{
    return m_scraper;
}

void Lector::onScraperGenres(const QString& artist, const QMap<int, QString>& genres_)
{
    if (artist.isEmpty() || genres_.isEmpty()) {
        qWarning() << "Empty values from scraper:" << "artist:" << artist << "genres:" << genres_;
    }

    QMap<int, QString> filteredGenres;
    QMapIterator<int, QString> it(genres_);
    it.toBack();
    while (it.hasPrevious()) {
        it.previous();

        // If we reached minimum genre weight or list is full, break
        if ((it.key() < minimumGenreWeight) || (filteredGenres.size() >= maximumGenreCount)) {
            break;
        }

        // If genre is blacklisted, continue
        if (isBlacklisted(it.value())) {
            continue;
        }

        // Add any genre that is above whitelistWeight or is in whitelist
        if ((it.key() >= whiteListGenreWeight) || isWhitelisted(it.value())) {
            filteredGenres.insertMulti(it.key(), it.value());
            // If genre is above whitelistWeight AND is in whitelist, this genre is distinct.
            if ((it.key() >= whiteListGenreWeight) && isWhitelisted(it.value())) {
                break;
            }
            continue;
        }

        // No whitelist genre, but maximumGenreCount not reached
        filteredGenres.insertMulti(it.key(), it.value());
    }

    for (auto& genre : filteredGenres) {
        spellCheck(genre);
    }

    emit genres(artist, filteredGenres);
}

bool Lector::isWhitelisted(const QString& genre)
{
    return false;
}

bool Lector::isBlacklisted(const QString& genre)
{
    if (genre.isEmpty()) {
        return true;
    }



    return false;
}

void Lector::spellCheck(QString& genre)
{
    if (genre.isEmpty()) {
        return;
    }

    // Capitalize first letter
    genre[0] = genre[0].toUpper();

    // Capitalize letters after " " and "-"
    QRegExp rx("[ -][a-z]");
    int pos = 0;
    while ((pos = rx.indexIn(genre, pos)) != -1) {
        genre[pos+1] = genre[pos+1].toUpper();
        pos += rx.matchedLength();
    }
}

} // namespace lector
