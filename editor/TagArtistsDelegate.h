#ifndef TAGARTISTSDELEGATE_H
#define TAGARTISTSDELEGATE_H

#include <QStyledItemDelegate>


class TagArtistsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TagArtistsDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // TAGARTISTSDELEGATE_H
