#include "SidebarItem.h"

#include <QStyleOptionButton>
#include <QStylePainter>


SidebarItem::SidebarItem(QWidget *parent) : QRadioButton(parent)
{
    connect(this, &QAbstractButton::toggled, this, &SidebarItem::onToggled);
}

void SidebarItem::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    p.translate(contentsRect().x() + 18, contentsRect().y());
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawControl(QStyle::CE_RadioButtonLabel, opt);
}

void SidebarItem::onToggled(bool checked)
{
    QFont f = font();
    f.setBold(checked);
    setFont(f);
}

void SidebarItem::setIndent(int indent)
{
    auto rect = contentsRect();
    rect.setLeft(rect.left() + indent);
}
