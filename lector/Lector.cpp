#include "Lector.h"

#include <QDebug>
#include <QRegExp>

#include "config/Config.h"

namespace lector {

Lector::Lector(QObject *parent)
    : CorrectorBase(parent),
      m_config(Config::instance().genres()),
      m_scraper(parent)
{
    connect(&Config::instance(), &Config::genresChanged, this, &Lector::onConfigChanged);

    connect(&m_scraper, &CorrectorBase::artist, this, &CorrectorBase::artist);
    connect(&m_scraper, &CorrectorBase::album, this, &CorrectorBase::album);
    connect(&m_scraper, &CorrectorBase::genres, this, &Lector::on_scraper_genres);
    connect(&m_scraper, &CorrectorBase::year, this, &CorrectorBase::year);

    // Load data from persistence
    m_blacklistModel.setStringList(m_config.blacklist);
    m_whitelistModel.setStringList(m_config.whitelist);
}

Lector::~Lector()
{
    // Store data to persistence
    config::Genres genres = Config::instance().genres();
    genres.blacklist = m_blacklistModel.stringList();
    genres.whitelist = m_whitelistModel.stringList();
    Config::instance().setGenres(genres);
}

GenreListModel* Lector::blacklistModel()
{
    return &m_blacklistModel;
}

GenreListModel* Lector::whitelistModel()
{
    return &m_whitelistModel;
}

void Lector::getGenres(const QString& artist)
{
    m_scraper.getGenres(artist);
}

void Lector::onConfigChanged()
{
    m_config = Config::instance().genres();
}

void Lector::on_scraper_genres(const QString& artist, const QMap<int, QString>& genres_)
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
        if ((it.key() < m_config.minimumGenreWeight) || (filteredGenres.size() >= m_config.maximumGenreCount)) {
            break;
        }

        // If genre is blacklisted, continue
        if (isBlacklisted(it.value())) {
            continue;
        }

        // Add any genre that is above autoConfirmWeight or is in whitelist
        if ((it.key() >= m_config.autoConfirmWeight) || isWhitelisted(it.value())) {
            filteredGenres.insertMulti(it.key(), it.value());
            // If genre is above autoConfirmWeight AND is in whitelist, this genre is distinct.
            if ((it.key() >= m_config.autoConfirmWeight) && isWhitelisted(it.value())) {
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

bool Lector::isBlacklisted(const QString& genre)
{
    if (genre.isEmpty()) {
        return true;
    }

    return m_blacklistModel.stringList().contains(genre, Qt::CaseInsensitive);
}

bool Lector::isWhitelisted(const QString& genre)
{
    if (genre.isEmpty()) {
        return false;
    }

    return m_whitelistModel.stringList().contains(genre, Qt::CaseInsensitive);
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
