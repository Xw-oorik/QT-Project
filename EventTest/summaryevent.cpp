#include "summaryevent.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>


//总结
SummaryEvent::SummaryEvent(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    ql = new SummaryLabel(this);
    ql->setText("事件传递");
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;"
                      );
    vblayout->addWidget(ql);

    //注册过滤器
    ql->installEventFilter(this);
}

//父类的事件处理，看事件有没有传过来
void SummaryEvent::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"SummaryEvent::mousePressEvent";
}

bool SummaryEvent::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ql && event->type()==QEvent::MouseButtonPress)
    {
        qDebug()<<" SummaryEvent::eventFilter";
        //return  默认是false
        // return true; //事件到此为止，过滤掉了
        return false;//事件接着传递

        //event->ignore();event->accept(); 同样在他里面这两个函数也不起作用
    }
    return QWidget::eventFilter(watched,event);
}
