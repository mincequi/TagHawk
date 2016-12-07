#include "DatabaseUtil.h"

#include "Defines.h"

#include <QDir>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QVariant>


namespace database {

void createKeyValueTable(QSqlDatabase& db, const QString& name)
{
    QString str("CREATE TABLE IF NOT EXISTS :table_name (key TEXT NOT NULL PRIMARY KEY, value BLOB NOT NULL)");
    str.replace(":table_name", name);

    QSqlQuery query(db);
    query.exec(str);
}

void createListTable(QSqlDatabase& db, const QString& name)
{
    QString str("CREATE TABLE IF NOT EXISTS :table_name (item TEXT NOT NULL PRIMARY KEY)");
    str.replace(":table_name", name);

    QSqlQuery query(db);
    query.exec(str);
}

void insert(QSqlDatabase& db, const QString& table, const QString& key, const QByteArray& value)
{
    QString str("INSERT INTO :table_name (key, value) VALUES (:key, :value)");
    str.replace(":table_name", table);

    QSqlQuery query(db);
    query.prepare(str);
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

void insert(QSqlDatabase& db, const QString& table, const QString& key, const QString& value)
{
    QString str("INSERT INTO :table_name (key, value) VALUES (:key, :value)");
    str.replace(":table_name", table);

    QSqlQuery query(db);
    query.prepare(str);
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

QByteArray select(QSqlDatabase& db, const QString& table, const QString& key)
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
