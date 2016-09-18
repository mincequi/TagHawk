#include "cache.h"

#include "common/DatabaseUtil.h"

Cache::Cache(QObject *parent)
    : QObject(parent),
      m_db(::database::openCache())
{
}

QStringList Cache::tables() const
{
    return m_db.tables();
}
