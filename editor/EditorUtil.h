#ifndef EDITORUTIL_H
#define EDITORUTIL_H

#include <QMap>


namespace editor {

QStringList toDisplayStringList(const QMap<int, QString>& map);
QStringList toEditStringList(const QMap<int, QString>& map);

} // namespace editor

#endif // EDITORUTIL_H
