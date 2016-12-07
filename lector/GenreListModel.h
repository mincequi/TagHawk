#ifndef GENRELISTMODEL_H
#define GENRELISTMODEL_H

#include <QStringListModel>


class GenreListModel : public QStringListModel
{
    Q_OBJECT

public:
    explicit GenreListModel(QObject *parent = 0);
    ~GenreListModel();

    void add(const QString& genre);
    void remove(const QString& genre);

signals:
    void changed();
};

#endif GENRELISTMODEL_H
