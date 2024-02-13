#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringList>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void addcitys(); //添加城市
    void getres(); //获取当前面板结果
    void clears(); //清空
private:
    Ui::Widget *ui;
    QList<QStringList> citylist;

private slots:
    void provice_city_change(int index);
};
#endif // WIDGET_H
