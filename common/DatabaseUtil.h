#ifndef DATABASEUTIL_H
#define DATABASEUTIL_H

#include <QSqlDatabase>


namespace database {

// Creates a simple key/value table with provided name.
void createKeyValueTable(QSqlDatabase& db, const QString& name);

// Creates a simple list table with provided name.
void createListTable(QSqlDatabase& db, const QString& name);

void insert(QSqlDatabase& db, const QString& table, const QString& key, const QByteArray& value);
void insert(QSqlDatabase& db, const QString& table, const QString& key, const QString& value);

QByteArray select(QSqlDatabase& db, const QString& table, const QString& key);
//QString select(const QString& table, const QString& key);


} // namespace database


#endif // DATABASEUTIL_H
