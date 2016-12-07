#ifndef CACHE_H
#define CACHE_H

#include <QSqlDatabase>


class Cache
{
public:
    static Cache& instance();

    QSqlDatabase& db();

private:
    Cache();
    ~Cache();

    static Cache* m_instance;

    QSqlDatabase    m_db;
};

#endif // CACHE_H
