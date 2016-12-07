#include "Config.h"


Config& Config::instance()
{
    static Config s_instance;
    return s_instance;
}

Config::Config() : QSettings(nullptr)
{
}

config::Genres Config::genres() const
{
    config::Genres genres;

    genres.maximumGenreCount    = value("genres/maximum_genre_count",  5).toInt();
    genres.minimumGenreWeight   = value("genres/minimum_genre_weight", 20).toInt();
    genres.whitelistWeight      = value("genres/whitelist_weight",     80).toInt();
    genres.whitelist            = value("genres/whitelist").toStringList();
    genres.blacklist            = value("genres/blacklist").toStringList();

    return genres;
}

void Config::setGenres(const config::Genres& genres_)
{
    if (genres_ == genres()) {
        return;
    }

    setValue("genres/maximum_genre_count",     genres_.maximumGenreCount);
    setValue("genres/minimum_genre_weight",    genres_.minimumGenreWeight);
    setValue("genres/whitelist_weight",        genres_.whitelistWeight);
    setValue("genres/whitelist",        genres_.whitelist);
    setValue("genres/blacklist",        genres_.blacklist);

    emit genresChanged();
}

config::Tags Config::tags() const
{
    config::Tags tags;

    tags.stripId3v1    = value("tags/strip_id3v1", true).toBool();

    return tags;
}

void Config::setTags(const config::Tags& tags_)
{
    if (tags_ == tags()) {
        return;
    }

    setValue("tags/strip_id3v1", tags_.stripId3v1);

    emit tagsChanged();
}
