#ifndef CORRECTARTISTSMODEL_H
#define CORRECTARTISTSMODEL_H

#include <QStandardItemModel>

class CorrectArtistModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit CorrectArtistModel(QObject *parent = 0);
    ~CorrectArtistModel();

    void setCanonicalName(const QString& original, const QString& canonical);
    QString canonicalName(const QString& original) const;
    QStringList originalNames(const QString& canonical) const;

signals:
    void artistRenamed(const QString& original, const QString& canonical, int* numFiles);
};

#endif // CORRECTARTISTSMODEL_H
