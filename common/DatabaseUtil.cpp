#include "DatabaseUtil.h"

#include "Defines.h"

#include <QDir>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QVariant>


namespace database {

static QSqlDatabase s_cacheDb;
static QSqlDatabase s_configDb;

QSqlDatabase openConfig()
{
    if (s_configDb.isOpen()) {
        return s_configDb;
    }

    auto location = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    location = location + QDir::separator() + common::configFile;

    s_configDb = QSqlDatabase::addDatabase("QSQLITE", "config");
    s_configDb.setDatabaseName(location);
    if (!s_configDb.open()) {
        qWarning() << "Cannot open database";
        return QSqlDatabase();
    }

    createListTable(s_configDb, lector::configTableGenreBlacklist);
    createListTable(s_configDb, lector::configTableGenreWhitelist);

    return s_configDb;
}

QSqlDatabase openCache()
{
    if (s_cacheDb.isOpen()) {
        return s_cacheDb;
    }

    auto location = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    location = location + QDir::separator() + common::cacheFile;

    s_cacheDb = QSqlDatabase::addDatabase("QSQLITE", "cache");
    s_cacheDb.setDatabaseName(location);
    if (!s_cacheDb.open()) {
        qWarning() << "Cannot open database";
        return QSqlDatabase();
    }

    createKeyValueTable(s_cacheDb, scraper::lastfm::cacheTableArtistCorrection);
    createKeyValueTable(s_cacheDb, scraper::lastfm::cacheTableArtistTopTags);

    return s_cacheDb;
}

void createKeyValueTable(QSqlDatabase db, const QString& name)
{
    QString str("CREATE TABLE IF NOT EXISTS :table_name (key TEXT NOT NULL PRIMARY KEY, value BLOB NOT NULL)");
    str.replace(":table_name", name);

    QSqlQuery query(db);
    query.exec(str);
}

void createListTable(QSqlDatabase db, const QString& name)
{
    QString str("CREATE TABLE IF NOT EXISTS :table_name (item TEXT NOT NULL PRIMARY KEY)");
    str.replace(":table_name", name);

    QSqlQuery query(db);
    query.exec(str);
}

void insert(QSqlDatabase db, const QString& table, const QString& key, const QByteArray& value)
{
    QString str("INSERT INTO :table_name (key, value) VALUES (:key, :value)");
    str.replace(":table_name", table);

    QSqlQuery query(db);
    query.prepare(str);
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

void insert(QSqlDatabase db, const QString& table, const QString& key, const QString& value)
{
    QString str("INSERT INTO :table_name (key, value) VALUES (:key, :value)");
    str.replace(":table_name", table);

    QSqlQuery query(db);
    query.prepare(str);
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

QByteArray select(QSqlDatabase db, const QString& table, const QString& key)
{
    QString str("SELECT value FROM :table_name where key = :key");
    str.replace(":table_name", table);

    QSqlQuery query(db);
    query.prepare(str);
    query.bindValue(":key", key);
    query.exec();

    if (query.next()) {
        return query.value(0).toByteArray();
    }

    return QByteArray();
}

bool exists(QSqlDatabase db, const QString& key)
{
    return false;
}

/*
QString select(const QString& table, const QString& key)
{
    QString str("SELECT value FROM :table_name where key = :key");
    str.replace(":table_name", table);

    QSqlQuery query;
    query.prepare(str);
    query.bindValue(":key", key);
    query.exec();

    if (query.next()) {
        return query.value(0).toString();
    }

    return QString();
}
*/

} // namespace database
