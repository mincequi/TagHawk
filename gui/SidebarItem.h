#ifndef SIDEBARITEM_H
#define SIDEBARITEM_H

#include <QRadioButton>

class SidebarItem : public QRadioButton
{
    Q_OBJECT
public:
    explicit SidebarItem(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

signals:

private slots:
    void onToggled(bool checked);
};

#endif // SIDEBARITEM_H
