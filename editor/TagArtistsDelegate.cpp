#include "TagArtistsDelegate.h"

#include <QComboBox>


TagArtistsDelegate::TagArtistsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* TagArtistsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != 1) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

    QComboBox* editor = new QComboBox(parent);
    return editor;
}

void TagArtistsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void TagArtistsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
}
