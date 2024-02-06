#include "mouse_press_move_realse.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include "labelp.h"

//鼠标按下移动离开
MousePressMoveRealse::MousePressMoveRealse(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    //1.
    LabelP *ql = new LabelP(this);
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:white;font:25px;background-color:rgb(120,120,120);border-radius:10px;");
    vblayout->addWidget(ql);

    //2.
    ws = new QWidget(this);
    qls = new QLabel(ws);
    qls->setFixedSize(95,95);
    qls->setFrameShape(QFrame::Box);
    qls->setStyleSheet("background-color: rgb(242,156,177)");
    vblayout->addWidget(ws);
    //注册过滤器
    qls->installEventFilter(this);


}

bool MousePressMoveRealse::eventFilter(QObject *watched, QEvent *event)
{
    if(watched != qls){
        return QWidget::eventFilter(watched,event);
    }
    if(event->type()==QEvent::MouseButtonPress){
        qDebug()<<"MouseButtonPress";
        QMouseEvent*ms=static_cast<QMouseEvent*>(event);
        presspos=ms->globalPos();
        labelpos=qls->pos();
    }
    else if(event->type()==QEvent::MouseButtonRelease){

        qDebug()<<"MouseButtonRelease";

    }
    else if(event->type()==QEvent::MouseMove){
        qDebug()<<"MouseMove";
        QMouseEvent*ms=static_cast<QMouseEvent*>(event);
        QPoint dstpos=labelpos+(ms->globalPos()-presspos);
        qls->move(dstpos);
        //超过左边
        if(qls->pos().x()<0){
            qls->move(0,qls->pos().y());
        }
        //右边
        if(qls->pos().x()>ws->width()-qls->width())
        {
            qls->move(ws->width()-qls->width(),qls->pos().y());
        }
        //上面
        if(qls->pos().y()<0){
            qls->move(qls->pos().x(),0);
        }
        //下面
        if(qls->pos().y()>ws->height()-qls->height())
        {
            qls->move(qls->pos().x(),ws->height()-qls->height());
        }
    }
}

