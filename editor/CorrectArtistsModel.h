#ifndef CORRECTARTISTSMODEL_H
#define CORRECTARTISTSMODEL_H

#include <QStandardItemModel>


class CorrectArtistsModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit CorrectArtistsModel(QObject *parent = 0);
    ~CorrectArtistsModel();

    // Artist correction is applied collection wide. It will not be specific to an album or whatever.
    void correct(const QString& misspelled, const QString& corrected);
};

#endif // CORRECTARTISTSMODEL_H
