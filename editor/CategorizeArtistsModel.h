#include <QStandardItemModel>

#include "config/Genres.h"


class CategorizeArtistsModel : public QStandardItemModel
{
    Q_OBJECT

public:
    enum ItemDataRole {
        TypeRole = Qt::UserRole + 10,
        WeightRole = Qt::UserRole + 11
    };

    enum ItemType {
        ArtistItem = 10,
        GenreItem = 12
    };

    explicit CategorizeArtistsModel(QObject *parent = 0);
    ~CategorizeArtistsModel();

    QMap<QString, QString> genres() const;

public slots:
    void setGenres(const QString& artist, const QMap<int, QString>& genres);

signals:
    void genreBlacklisted(const QString& genre);
    void genreWhitelisted(const QString& genre);
    void artistCategorized(const QString& artist, const QString& genre);

private:
    void onConfigChanged();

    config::Genres  m_config;
};
