#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QButtonGroup>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void InitNavigation();
    void InitMainWidget();
private slots:
    void tt();//左边按钮和右边页面对应信号槽

private:
    QWidget *navWidget; //左边的导航widget,里面放多个button 和右边的页面对应起来
    QWidget *mainWidget; //右侧的主体widget，里面stack放一个个界面
    QStackedWidget *stackWidget;//放右边页面
    QButtonGroup *btngp;//放左侧按钮
};
#endif // WIDGET_H
