#ifndef CORRECTORBASE_H
#define CORRECTORBASE_H

#include <QObject>

class CorrectorBase : public QObject
{
    Q_OBJECT
public:
    explicit CorrectorBase(QObject *parent = 0);

    virtual void getArtist(const QString& artist);
    virtual void getAlbum(const QString& artist, const QString& album);
    virtual void getGenres(const QString& artist);
    virtual void getYear(const QString& artist, const QString& album);

signals:
    void artist(const QString& misspelled, const QString& corrected);
    void album(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum);
    void genres(const QString& artist, const QMap<int, QString>& genres);
    void year(const QString& artist, const QString& album, const QString& year);
};

#endif // CORRECTORBASE_H
