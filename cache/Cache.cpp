#include "Cache.h"

#include <QDir>
#include <QSqlError>
#include <QStandardPaths>


#include "Defines.h"
#include "common/DatabaseUtil.h"


Cache* Cache::m_instance = nullptr;

Cache& Cache::instance()
{
    if (!m_instance) {
        m_instance = new Cache();
    }

    return *m_instance;
}

QSqlDatabase& Cache::db()
{
    return m_db;
}

Cache::Cache()
{
    auto location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    QDir().mkpath(location);
    location = location + QDir::separator() + common::cacheFile;

    m_db = QSqlDatabase::addDatabase("QSQLITE", "cache");
    m_db.setDatabaseName(location);
    if (!m_db.open()) {
        qWarning() << "Cannot open database:" << m_db.lastError();
        m_db = QSqlDatabase();
        return;
    }
}

Cache::~Cache()
{
}
