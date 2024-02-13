#ifndef WIDGET_H
#define WIDGET_H

#include "task.h"

#include <QWidget>
#include <QThreadPool>

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
    Task *task;
};
#endif // WIDGET_H
