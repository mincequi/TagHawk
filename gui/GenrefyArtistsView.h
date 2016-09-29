#ifndef GENREFYARTISTSVIEW_H
#define GENREFYARTISTSVIEW_H

#include <QStandardItemModel>
#include <QTreeView>


class GenrefyArtistsView : public QTreeView
{
    Q_OBJECT

public:
    // @TODO(mawe): need to provide black/whitelist model
    explicit GenrefyArtistsView(QWidget *parent = 0);
    ~GenrefyArtistsView();

private:
    void onContextMenuRequested(const QPoint& pos);
    void checkSelection(Qt::CheckState state);
};

#endif // GENREFYARTISTSVIEW_H
