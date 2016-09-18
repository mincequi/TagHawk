#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>
#include <QStringList>


namespace common {
static const char* configFile  = "bagga_config.sqlite";
static const char* cacheFile  = "bagga_cache.sqlite";
} // namespace common

namespace lector {
static const char* database  = "lector.sqlite";
static const int whiteListGenreWeight = 80; // Genres above or equal this value will always be recommended.
static const int minimumGenreWeight = 20; // Genres below this value will be dropped.
static const int minimumGenreCount = 1;
static const int maximumGenreCount = 5; // Maximum numbers of genres to be recommended

static const char* configTableGenreWhitelist   = "genre_whitelist";
static const char* configTableGenreBlacklist   = "genre_blacklist";
} // namespace lector

namespace reader {
static const QStringList supportedExtensions {
    "*.mp3"
};
} // namespace reader

namespace scraper {
namespace lastfm {

static const char* applicationName  = "bagga";
static const char* apiKey           = "cd870f94e376f3d6f0a30eb17598d0fd";
static const char* sharedSecret     = "e1f5bda3bcbf9880131936b8e35d31e5";

static QString apiMethodArtistGetTopTags = "artist.getTopTags";
//static const char* apiMethodAlbum = "abcabcabcabcabcabcabc";
//static const char* apiMethodAlbum = "abcabcabcabcabcabcabc";

static const char* cacheTableArtistCorrection   = "lastfm_artist_correction";
static const char* cacheTableArtistTopTags      = "lastfm_artist_top_tags";

} // namespace lastfm
} // namespace scraper

#endif // DEFINES_H
