#include "keyboard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>

//键盘事件
KeyBoard::KeyBoard(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);
    //1
    QLabel *ql = new QLabel(this);
    ql->setText("键盘事件");
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;"
                      );
    vblayout->addWidget(ql);
    //2
    qls = new QLabel(this);
    qls->setFixedSize(75,75);
    qls->setFrameShape(QFrame::Box);
    qls->setStyleSheet("background-color:red");
    vblayout->addWidget(qls);
    //..
    setFocusPolicy(Qt::StrongFocus);//设置控制焦点策略
    this->grabKeyboard();//具有捕获键盘事件的能力
}

void KeyBoard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
        qDebug()<<"Enter";

    case Qt::Key_Up:
        qDebug()<<"up";
        qls->move(qls->x(),qls->y()-10);
        if(qls->y()+qls->height()<=0){
            qls->move(qls->x(),this->height());
        }
        break;
    case Qt::Key_Down:
        qDebug()<<"Down";
        qls->move(qls->x(),qls->y()+10);
        if(qls->y()>=this->height()){
            qls->move(qls->x(),0);
        }
        break;
    case Qt::Key_Left:
        qDebug()<<"left";
        qls->move(qls->x()-10,qls->y());
        if(qls->x()+qls->width()<=0){
            qls->move(this->width(),qls->y());
        }
        break;
    case Qt::Key_Right:
        qDebug()<<"Right";
        qls->move(qls->x()+10,qls->y());
        if(qls->x()>=this->width()){
            qls->move(0,qls->y());
        }
        break;
    case Qt::Key_Shift:
        qDebug()<<"Shift";
        break;
    case Qt::Key_Alt:
        qDebug()<<"Alt";
        break;
    case Qt::Key_Escape:
        qDebug()<<"Escape";
        break;
    default:
        break;
    }

    //两个按键
    if((event->modifiers()==Qt::ControlModifier)&&(event->key()==Qt::Key_A)){
        qDebug()<<"Ctrl+A";
    }
    //三个按键
    if((event->modifiers()==(Qt::ControlModifier|Qt::ShiftModifier))&&(event->key()==Qt::Key_A)){
        qDebug()<<"Ctrl+Shift+A";
    }
}

void KeyBoard::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
        qDebug()<<"keyReleaseEvent Enter";
        break;
    case Qt::Key_Up:
        qDebug()<<"keyReleaseEvent up";
        break;
    case Qt::Key_Down:
        qDebug()<<"keyReleaseEvent Down";
        break;
    case Qt::Key_Shift:
        qDebug()<<"keyReleaseEvent Shift";
        break;
    case Qt::Key_Alt:
        qDebug()<<"keyReleaseEvent Alt";
        break;
    case Qt::Key_Escape:
        qDebug()<<"keyReleaseEvent Escape";
        break;
    default:
        break;
    }
}
