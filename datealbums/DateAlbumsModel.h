#ifndef DATEALBUMSMODEL_H
#define DATEALBUMSMODEL_H

#include <QStandardItemModel>

class DateAlbumsModel : public QStandardItemModel
{
public:
    DateAlbumsModel();

public slots:
    // Year is applied to specified album from specified artist.
    void setYear(const QString& artist, const QString& album, const QString& year);
};

#endif // DATEALBUMSMODEL_H
