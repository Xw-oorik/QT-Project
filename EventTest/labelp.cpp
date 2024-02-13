#include "labelp.h"
#include <QMouseEvent>
#include <QDebug>

LabelP::LabelP(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true); //设置鼠标追踪，就是不用点击
}
static int i=1;
void LabelP::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setText(QString("enterEvent: %1").arg(i++));
}

void LabelP::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setText(QString("leaveEvent: %1").arg(i++));
}

void LabelP::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug()<<"鼠标追击移动"<<ev->globalPos()<<ev->x()<<ev->y();
    if(ev->buttons()&Qt::LeftButton)
    {
        qDebug()<<"鼠标点击移动"<<ev->globalPos()<<ev->x()<<ev->y();
    }

}

void LabelP::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
      qDebug()<<"鼠标按下 "<<ev->pos()<<ev->globalPos()<<ev->x()<<ev->y();
    }
}

void LabelP::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
      qDebug()<<"鼠标释放 "<<ev->pos()<<ev->globalPos()<<ev->x()<<ev->y();
    }
}
