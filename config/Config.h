#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

#include "Genres.h"
#include "Tags.h"


class Config : public QSettings
{
    Q_OBJECT

public:
    static Config& instance();

    config::Genres genres() const;
    void setGenres(const config::Genres& genres);

    config::Tags tags() const;
    void setTags(const config::Tags& tags);

signals:
    void genresChanged();
    void tagsChanged();

private:
    Config();

    static Config* m_instance;
};

#endif // CONFIG_H
