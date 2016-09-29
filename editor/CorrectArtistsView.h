#ifndef CORRECTARTISTSVIEW_H
#define CORRECTARTISTSVIEW_H

#include <QStandardItemModel>
#include <QTreeView>


class CorrectArtistsView : public QTreeView
{
    Q_OBJECT

public:
    explicit CorrectArtistsView(QWidget *parent = 0);
    ~CorrectArtistsView();

    void correct(const QString& uncorrected, const QString& corrected);

private:
    void onContextMenuRequested(const QPoint& pos);
    void checkSelection(Qt::CheckState state);

    QStandardItemModel* m_model;
};

#endif // CORRECTARTISTSVIEW_H
