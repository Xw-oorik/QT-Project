#include "rightclick.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

// 右键 事件
RightClick::RightClick(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    QLabel *ql = new QLabel(this);
    ql->setText("右键事件");
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;"
                      );
    vblayout->addWidget(ql);


    //
    setContextMenuPolicy(Qt::DefaultContextMenu);//基于窗口的菜单策略实现,
    //基于事件处理器函数 QWidget::contextMenuEvent() 实现
}

//用鼠标事件去完成
void RightClick::mousePressEvent(QMouseEvent *event)
{
  /*  if(event->button()==Qt::RightButton){
        QMenu *menu=new QMenu(this);
        cnt= new QAction("剪切(T)",this);
        copy= new QAction("拷贝(C)",this);
        hide= new QAction("隐藏行",this);

        menu->addAction(cnt);
        menu->addAction(copy);
        menu->addAction(hide);
        connect(cnt,&QAction::triggered,this,&RightClick::righttrigger);
        connect(copy,&QAction::triggered,this,&RightClick::righttrigger);
        connect(hide,&QAction::triggered,this,&RightClick::righttrigger);
        menu->exec(event->globalPos());

    }*/
}

void RightClick::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu=new QMenu();
    cnt= new QAction("剪切(T)",this);
    copy= new QAction("拷贝(C)",this);
    hide= new QAction("隐藏行",this);

    menu->addAction(cnt);
    menu->addAction(copy);
    menu->addAction(hide);
    connect(cnt,&QAction::triggered,this,&RightClick::righttrigger);
    connect(copy,&QAction::triggered,this,&RightClick::righttrigger);
    connect(hide,&QAction::triggered,this,&RightClick::righttrigger);
    menu->exec(event->globalPos());
    delete menu;
}

void RightClick::righttrigger()
{
    QAction* tmp=dynamic_cast<QAction*>(sender());
    qDebug()<<tmp->text();
    if(tmp==cnt){
        qDebug()<<"点击剪切(T)";
    }
}
