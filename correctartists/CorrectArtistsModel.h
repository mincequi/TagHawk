#ifndef CORRECTARTISTSMODEL_H
#define CORRECTARTISTSMODEL_H

#include <QStandardItemModel>

class CorrectArtistsModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit CorrectArtistsModel(QObject *parent = 0);
    ~CorrectArtistsModel();

    void setCanonicalName(const QString& original, const QString& canonical);
    QString canonicalName(const QString& original) const;
    QStringList originalNames(const QString& canonical) const;

signals:
    void artistRenamed(const QString& original, const QString& canonical, int* numFiles);
};

#endif // CORRECTARTISTSMODEL_H
