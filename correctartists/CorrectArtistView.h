#ifndef CORRECTARTISTSVIEW_H
#define CORRECTARTISTSVIEW_H

#include <QTreeView>


class CorrectArtistView : public QTreeView
{
    Q_OBJECT

public:
    explicit CorrectArtistView(QWidget *parent = 0);
    ~CorrectArtistView();

private:
    void onContextMenuRequested(const QPoint& pos);
    void checkSelection(Qt::CheckState state);
};

#endif // CORRECTARTISTSVIEW_H
