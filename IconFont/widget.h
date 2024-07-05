#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    bool eventFilter(QObject* watched, QEvent *event);
private:
    void radioClicked();
private:
    QButtonGroup* radioGroup;  //字体库选择
    QGridLayout* gridLayout;   //图片布局

    QLabel* lblRed;
    QLabel* lblOrange;
    QLabel* lblYellow;
    QLabel* lblGreen;
    QLabel* lblCyan;
    QLabel* lblBlue;
    QLabel* lblPurple;
    QList<QLabel*> lblList;
};
#endif // WIDGET_H
