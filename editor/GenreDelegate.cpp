#include "TagArtistsDelegate.h"

#include <QComboBox>
#include <QStandardItemModel>


TagArtistsDelegate::TagArtistsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* TagArtistsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != 1) {
        return NULL;
    }

    QComboBox* editor = new QComboBox(parent);

    const QStandardItemModel* model = static_cast<const QStandardItemModel*>(index.model());
    editor->addItems(model->itemFromIndex(index)->data(Qt::UserRole+1).toStringList());
    return editor;
}

void TagArtistsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void TagArtistsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() != 1) {
        return;
    }

    QComboBox* comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, model->data(index, Qt::UserRole+2).toStringList().at(comboBox->currentIndex()));
}
