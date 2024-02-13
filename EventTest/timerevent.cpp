#include "timerevent.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>




//  定时器事件
/*
 * 做定时器有两种方式，一种QTimer类，一种是QEvent的Timer事件 ，用到的子类是QTimerEvent
 * 用两种都去实现一下
 * 1.QTimerEvent
 * 需要重写void QObject::timerEvent(QTimerEvent *event)
 * 当定时时间到的时候会自动调用timerEvent
 * 用timerid可以获取哪个定时器的id
 * startTimer()可以设置定时器时间间隔 ms
 * killTimer停止定时器
 *
 * 2.
 *QTimer 需要创建QTimer对象
 * 然后需要给定时器绑定 定时器超时的槽函数
 * 一般在按钮里面有start，stop就是控制定时器的
 * 这样通过按钮点击之后，调用里面Qtimer的start，因为外面绑定了定时器超时槽函数，所以
 * 定时器到时间了就会调用超时槽函数
 * 对于 QTimerEvent不用重写超时函数并且去手动绑定，他会自动调用timerEvent，只需要重写这个就行
 * */
TimerEvent::TimerEvent(QWidget *parent) : QWidget(parent)
{
    //垂直布局
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    //
    QLabel *ql = new QLabel(this);
    ql->setText("定时器事件");
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;"
                      );
    vblayout->addWidget(ql);

    //第一个标签
    lab1 = new QLabel(this);
    lab1->setFixedSize(95,95);
    lab1->setFrameShape(QFrame::Box);
    lab1->setStyleSheet("background-color:yellow");
    vblayout->addWidget(lab1);
    //第二个标签
    lab2 = new QLabel(this);
    lab2->setFixedSize(95,95);
    lab2->setFrameShape(QFrame::Box);
    lab2->setStyleSheet("background-color:purple");
    vblayout->addWidget(lab2);
    //三个按钮
    QPushButton* start= new QPushButton(this);
    start->setText("开始");
    QPushButton* pause= new QPushButton(this);
    pause->setText("暂停");
    QPushButton* restart= new QPushButton(this);
    restart->setText("复位");
    this->setStyleSheet(R"(
                        QPushButton{
                        font-size:20px;
                        })");
    //水平布局
    QHBoxLayout *hb = new QHBoxLayout(this);
    hb->setSpacing(0);
    hb->setContentsMargins(0,0,0,0);

    hb->addWidget(start);
    hb->addWidget(pause);
    hb->addWidget(restart);
    vblayout->addLayout(hb);

    //按键的信号槽
    connect(start,&QPushButton::clicked,this,&TimerEvent::startclick);
    connect(pause,&QPushButton::clicked,this,&TimerEvent::pauseclick);
    connect(restart,&QPushButton::clicked,this,&TimerEvent::restartclick);

    //Qtimer绑定的信号槽
    tm1 = new QTimer(this);
    tm2 = new QTimer(this);
    connect(tm1,&QTimer::timeout,this,&TimerEvent::timerout1);
    connect(tm2,&QTimer::timeout,this,&TimerEvent::timerout2);
}

void TimerEvent::startclick()
{
#ifdef USR_TIMER_EVENT
    qDebug()<<"use timerevent";
    id1=startTimer(10);
    id2=startTimer(20);
#else
    qDebug()<<"use Qtimer";
    tm1->start(10);
    tm2->start(20);
#endif
}

void TimerEvent::pauseclick()
{
#ifdef USR_TIMER_EVENT
    qDebug()<<"use timerevent";
    killTimer(id1);
    killTimer(id2);
#else
    qDebug()<<"use Qtimer";
    tm1->stop();
    tm2->stop();
#endif
}

void TimerEvent::restartclick()
{
    lab1->move(0,lab1->y());
    lab2->move(0,lab2->y());
}
//Qtimer
void TimerEvent::timerout1()
{
    lab1->move(lab1->x()+5,lab1->y());
    if(lab1->x()>=this->width()){
        lab1->move(0,lab1->y());
    }

}

void TimerEvent::timerout2()
{
    lab2->move(lab2->x()+5,lab2->y());
    if(lab2->x()>=this->width()){
        lab2->move(0,lab2->y());
    }
}
//timerevent
void TimerEvent::timerEvent(QTimerEvent *event)
{
    //当定时器时间到了，看是哪个定时器
    if(event->timerId()==id1){
        lab1->move(lab1->x()+5,lab1->y());
        if(lab1->x()>=this->width()){
            lab1->move(0,lab1->y());
        }
    }
    if(event->timerId()==id2){
        lab2->move(lab2->x()+5,lab2->y());
        if(lab2->x()>=this->width()){
            lab2->move(0,lab2->y());
        }
    }
}
