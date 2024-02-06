#ifndef TIMEREVENT_H
#define TIMEREVENT_H

#include <QWidget>
#include <QTimer>
#include <QTimerEvent>
#include <QLabel>

class TimerEvent : public QWidget
{
    Q_OBJECT
public:
    explicit TimerEvent(QWidget *parent = nullptr);
private slots:
    void startclick();
    void pauseclick();
    void restartclick();

    //用QTimer，定时器超时的槽函数
    void timerout1();
    void timerout2();
private:
    QLabel* lab1;
    QLabel* lab2;
    int id1;
    int id2;
    //QTimer
    QTimer *tm1;
    QTimer *tm2;
private:
    //QTimerEvent
    void timerEvent(QTimerEvent *event);
signals:

};

#endif // TIMEREVENT_H
