#include "EditorUtil.h"


namespace editor {

QStringList toDisplayStringList(const QMap<int, QString>& map)
{
    QStringList list;
    QMapIterator<int, QString> it(map);
    it.toBack();
    while (it.hasPrevious()) {
        it.previous();
        list << QString(it.value() + " (" + QString::number(it.key()) + ")");
    }
    return list;
}

QStringList toEditStringList(const QMap<int, QString>& map)
{
    QStringList list;
    QMapIterator<int, QString> it(map);
    it.toBack();
    while (it.hasPrevious()) {
        it.previous();
        list << it.value();
    }
    return list;
}

} // namespace editor
