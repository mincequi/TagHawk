#include "sidebaritem.h"

#include <QStyleOptionButton>
#include <QStylePainter>


SidebarItem::SidebarItem(QWidget *parent) : QRadioButton(parent)
{
    connect(this, &QAbstractButton::toggled, this, &SidebarItem::onToggled);
}

void SidebarItem::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawControl(QStyle::CE_RadioButton, opt);
}

void SidebarItem::onToggled(bool checked)
{
    QFont f = font();
    f.setBold(checked);
    setFont(f);
}
