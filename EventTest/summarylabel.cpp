#include "summarylabel.h"
#include <QDebug>
#include <QMouseEvent>

SummaryLabel::SummaryLabel(QWidget *parent) : QLabel(parent)
{

}

void SummaryLabel::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"SummaryLabel::mousePressEvent";
    qDebug()<<event->isAccepted();
    //接受事件
    //event->accept();
    //qDebug()<<"SummaryLabel::mousePressEvent accept";

    //忽略事件，就会继续传递到父控件(上层窗口)
    event->ignore();
    qDebug()<<"SummaryLabel::mousePressEvent ignore";

}

bool SummaryLabel::event(QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        qDebug()<<"SummaryLabel::event -> mousePressEvent";
        //1.
        //event->accept(); //在event函数里面调用accept或者ignore是没用的

        //2.
        //所以说在检测到这个MouseButtonPress事件之后，不接受这个事件
        //想要不再传递这个事件就直接return true，这样事件的传递就到此为止，不会再去走任何函数了
        //return true;

        //3.
        //但是返回false的话，表示这个MouseButtonPress事件没有被识别
        //也就是不会走到我们SummaryLabel的mousePressEvent函数，而是跳过他
        //直接走到父类的mousePressEvent函数
        return false;
    }
    //其余没有做判断的事件最后 都会调用父类的控制，也就是会走到父类控件去
    //保证其他事件按照默认的分发流程进行分发
    //这个函数一般最后都会这么写
    return QWidget::event(event);
}

