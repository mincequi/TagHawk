#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

class QAbstractButton;
class QAbstractItemModel;
class QStackedWidget;
class QWidget;


template <typename T>
void createView(QStackedWidget* stack, QAbstractButton* button, QAbstractItemModel* model);


#endif // VIEWFACTORY_H
