#include "painterevent.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QRandomGenerator64>

//14个点，13个间隔，，左右两边我们留50个像素点
#define POINTEXT 20
#define INCREMENT  8//曲线像素增量
#define POINT_RADIUS 4 //曲线描点的大小
#define TEXT_OFFEST_X 6 //温度相对于点的偏移
#define TEXT_OFFEST_Y 6



// 绘图事件
/*
 * 两种实现，第一种是自定义标签控件，重写我们自定义的控件的 paintevent
 * 第二种是用事件过滤器，直接绘制到标准 QLabel
 *
 * 过滤器一般都是给要给要拦截的控件注册installEventFilter 过滤器，然后重写eventFilter函数
 *
 * 这里使用过滤器的方法写的
 * */
PainterEvent::PainterEvent(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,0,0,0);

    QLabel *ql = new QLabel(this);
    ql->setText("绘图事件");
    ql->setFixedHeight(50);
    ql->setAlignment(Qt::AlignCenter);
    ql->setFrameShape(QFrame::Box);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;");
    vblayout->addWidget(ql);

    //high label
    labhigh = new QLabel(this);
    labhigh->setFrameShape(QFrame::StyledPanel);
    vblayout->addWidget(labhigh);
    //low label
    lablow = new QLabel(this);
    lablow->setFrameShape(QFrame::StyledPanel);
    vblayout->addWidget(lablow);
    //更新随机
    updateT();
    //安装过滤器 ,拦截，然后调用到eventFilter 处理函数
    labhigh->installEventFilter(this);
    lablow->installEventFilter(this);

}

bool PainterEvent::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint)
    {
        if(watched==labhigh)
        {
            qDebug()<<u8"绘制高温曲线";
            painthigh();
        }
        else if(watched==lablow)
        {
            qDebug()<<u8"绘制低温曲线";
            paintlow();
        }
    }
    else if(event->type()==QEvent::MouseButtonDblClick){//双击更新
        updateT();
    }
    return QWidget::eventFilter(watched, event);
}
void PainterEvent::painthigh()
{
    QPainter painter(labhigh);
    painter.setRenderHint(QPainter::Antialiasing,true); //抗锯齿
    //计算x坐标
    int Pointx[14]{0};
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0]);++i)
    {
        Pointx[i]=labhigh->pos().x()+POINTEXT+(labhigh->width()-POINTEXT*2)/13*i;
    }
    //计算y坐标
    int tempsum=0;
    int temparg=0;
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0]);++i)
    {
        tempsum+=highnum[i];
    }
    temparg=tempsum/14;
    int Pointy[14]{0};
    int ycenter=labhigh->height()/2;
    int increment=labhigh->height()/20;
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0]);++i)
    {
        Pointy[i]=ycenter-((highnum[i]-temparg)*increment);
    }
    //开始绘制
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);
    painter.setBrush(QColor(Qt::yellow));
    painter.setFont(QFont("Microsoft YaHei", 10));
    //画点，写文本
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0]);++i)
    {
        painter.drawEllipse(Pointx[i],Pointy[i],POINT_RADIUS,POINT_RADIUS);
        painter.drawText(Pointx[i]-TEXT_OFFEST_X,Pointy[i]-TEXT_OFFEST_Y,QString::number(highnum[i])+"°");
    }
    //画线
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0])-1;++i)
    {
        if(!(i%2)){
            pen.setStyle(Qt::DotLine);

        }
        else{
            pen.setStyle(Qt::SolidLine);

        }
        painter.setPen(pen);
        painter.drawLine(Pointx[i],Pointy[i],Pointx[i+1],Pointy[i+1]);
    }
}

void PainterEvent::paintlow()
{
    QPainter painter(lablow);
    painter.setRenderHint(QPainter::Antialiasing,true); //抗锯齿
    //计算x坐标
    int Pointx[14]{0};
    for(int i=0;i<sizeof (lownum)/sizeof (lownum[0]);++i)
    {
        Pointx[i]=lablow->pos().x()+POINTEXT+(lablow->width()-POINTEXT*2)/13*i;
    }
    //计算y坐标
    int tempsum=0;
    int temparg=0;
    for(int i=0;i<sizeof (lownum)/sizeof (lownum[0]);++i)
    {
        tempsum+=lownum[i];
    }
    temparg=tempsum/14;
    int Pointy[14]{0};
    int ycenter=lablow->height()/2;
    int increment=lablow->height()/20;
    for(int i=0;i<sizeof (lownum)/sizeof (lownum[0]);++i)
    {
        Pointy[i]=ycenter-((lownum[i]-temparg)*increment);
    }
    //开始绘制
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(Qt::blue));
    painter.setPen(pen);
    painter.setBrush(QColor(Qt::green));
    painter.setFont(QFont("Microsoft YaHei", 10));
    //画点，写文本
    for(int i=0;i<sizeof (lownum)/sizeof (lownum[0]);++i)
    {
        painter.drawEllipse(Pointx[i],Pointy[i],POINT_RADIUS,POINT_RADIUS);
        painter.drawText(Pointx[i]-TEXT_OFFEST_X,Pointy[i]-TEXT_OFFEST_Y,QString::number(lownum[i])+"°");
    }
    //画线
    for(int i=0;i<sizeof (lownum)/sizeof (lownum[0])-1;++i)
    {
        if(!(i%2)){
            pen.setStyle(Qt::DotLine);

        }
        else{
            pen.setStyle(Qt::SolidLine);

        }
        painter.setPen(pen);
        painter.drawLine(Pointx[i],Pointy[i],Pointx[i+1],Pointy[i+1]);
    }
}

void PainterEvent::updateT()
{
    for(int i=0;i<sizeof (highnum)/sizeof (highnum[0]);++i)
    {
        highnum[i]=20+QRandomGenerator64::global()->generate64()%20;
        lownum[i]=-10+QRandomGenerator64::global()->generate64()%10;
    }
    labhigh->update();
    lablow->update();
}
