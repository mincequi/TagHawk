#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>
#include <QStringList>


namespace common {
static const char cacheFile[]  = "cache.sqlite";
} // namespace common

namespace collection {
static const QStringList supportedExtensions {
    "*.mp3"
};
} // namespace reader

namespace scraper {
namespace lastfm {

//static const char* applicationName  = "bagga";
static const char apiKey[]           = "cd870f94e376f3d6f0a30eb17598d0fd";
static const char sharedSecret[]     = "e1f5bda3bcbf9880131936b8e35d31e5";

static const char cacheTableArtistCorrection[]  = "lastfm_artist_correction";
static const char cacheTableArtistTopTags[]     = "lastfm_artist_top_tags";

} // namespace lastfm
} // namespace scraper

#endif // DEFINES_H
