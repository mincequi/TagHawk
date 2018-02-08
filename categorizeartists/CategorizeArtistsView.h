#ifndef CATEGORIZEARTISTSVIEW_H
#define CATEGORIZEARTISTSVIEW_H

#include <QTreeView>

class CategorizeArtistsView : public QTreeView
{
    Q_OBJECT

public:
    // @TODO(mawe): need to provide black/whitelist model
    explicit CategorizeArtistsView(QWidget *parent = 0);
    ~CategorizeArtistsView();

    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

private:
    void onDoubleClicked(const QModelIndex& index);
    void onContextMenuRequested(const QPoint& pos);
    void checkSelection(Qt::CheckState state);
};

#endif // CATEGORIZEARTISTSVIEW_H
