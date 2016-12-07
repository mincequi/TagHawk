#ifndef GENREVIEW_H
#define GENRESVIEW_H

#include <QListView>


class GenreListView : public QListView
{
public:
    explicit GenreListView(QWidget *parent = 0);
    ~GenreListView();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU

private:
    void removeSelection();

};

#endif // GENRESVIEW_H
