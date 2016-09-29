#ifndef EDITORUTIL_H
#define EDITORUTIL_H

#include <QMap>

class QStandardItem;


namespace editor {

QList<QStandardItem*> prepareRow(const QString& artist, const QMap<int, QString>& genres);

} // namespace editor

#endif // EDITORUTIL_H
