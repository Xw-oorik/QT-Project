#ifndef WIDGET_H
#define WIDGET_H

#include "framewidget.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Widget : public FrameWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void changeEvent(QEvent *ev);

private:
    void initFrom();
private:
    //上面标题栏相关
    QWidget *title_widget;
    QLabel *title_icon;
    QLabel *title_text;
    QPushButton *close_btn;
    QPushButton *zoom_btn;
    QPushButton *max_btn;

    //下面主窗口
    QWidget *main_widget;
};
#endif // WIDGET_H
