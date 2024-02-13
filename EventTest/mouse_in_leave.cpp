#include "mouse_in_leave.h"

#include <QVBoxLayout>
#include <QLabel>
#include "labelp.h"


//鼠标进入离开
MouseInLeave::MouseInLeave(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    //用自定义控件演示
    LabelP *ql = new LabelP(this);
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:red;font:25px;background-color:rgb(0,233,233);border-radius:10px;");
    vblayout->addWidget(ql);

    //用事件过滤器去演示
    qls=new QLabel(this);
    qls->setFixedHeight(50);
    qls->setAlignment(Qt::AlignCenter);
    qls->setFrameShape(QFrame::Box);
    qls->setStyleSheet("color:green;font:25px;background-color:rgb(122,210,215);border-radius:10px;");
    vblayout->addWidget(qls);
    //注册过滤器
    qls->installEventFilter(this); //给qls发的消息会被this窗口拦截


}

static int cnt=1;
bool MouseInLeave::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==qls){
        if(event->type()==QEvent::Enter){
            qls->setText(QString("enterEvent: %1").arg(cnt++));
        }
        else if(event->type()==QEvent::Leave){
            qls->setText(QString("leaveEvent: %1").arg(cnt++));
        }
    }
    return QWidget::eventFilter(watched,event);
}
