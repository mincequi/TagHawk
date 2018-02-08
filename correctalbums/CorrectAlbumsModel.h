#ifndef CORRECTALBUMSMODEL_H
#define CORRECTALBUMSMODEL_H

#include <QStandardItemModel>

class CorrectAlbumsModel : public QStandardItemModel
{
public:
    CorrectAlbumsModel();

public slots:
    // Album correction is limited to provided artist name.
    void correct(const QString& artist, const QString& misspelledAlbum, const QString& correctedAlbum);
};

#endif // CORRECTALBUMSMODEL_H
