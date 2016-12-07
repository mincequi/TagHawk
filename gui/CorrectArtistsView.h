#ifndef CORRECTARTISTSVIEW_H
#define CORRECTARTISTSVIEW_H

#include <QTreeView>


class CorrectArtistsView : public QTreeView
{
    Q_OBJECT

public:
    explicit CorrectArtistsView(QWidget *parent = 0);
    ~CorrectArtistsView();

private:
    void onContextMenuRequested(const QPoint& pos);
    void checkSelection(Qt::CheckState state);
};

#endif // CORRECTARTISTSVIEW_H
