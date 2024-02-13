#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "mytasks.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;

    QThread *th1;
    QThread *th2;
    MyTasks *tak1;
    MyTasks *tak2;
};
#endif // WIDGET_H
