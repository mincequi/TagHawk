#ifndef CACHE_H
#define CACHE_H

#include <QObject>
#include <QSqlDatabase>


class Cache : public QObject
{
    Q_OBJECT
public:
    explicit Cache(QObject *parent = 0);

    QStringList tables() const;

signals:

public slots:

private:
    QSqlDatabase    m_db;
};

#endif // CACHE_H
