#include "paintwidget.h"
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground,true);

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    //设置四个点，去来画
    static const QPoint points[4]{
        QPoint(10,80),QPoint(20,90),QPoint(80,10),QPoint(90,20)
    };
    QPainter painter(this);
    painter.setPen(m_pen);
    painter.setBrush(m_brush);
    if(m_status==Qt::Checked)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }
    QRect rect(points[1],points[2]);
    QPainterPath path;
    path.moveTo(5,5);//移动到指定点，开始指定路径
    path.lineTo(20,60); //以直线方式
    //贝瑟尔曲线的方式
    //path.cubicTo(QPoint(40,40),QPoint(60,60),QPoint(80,80));
    for(int x=0;x<this->width();x+=100)
    {
        for(int y=0;y<this->height();y+=100){
            painter.save();
            painter.translate(x,y);//更改坐标原点，这样的话各个端点相对的位置也不变
            if(m_move_transfrom==Qt::Checked ){
                painter.translate(50,50);
                painter.rotate(90.0);
                painter.scale(0.8,0.8);
                painter.translate(-50,-50);
            }
            switch (m_shape) {
                case Shape::_Point:
                painter.drawPoints(points,4);
                break;
            case Shape::_Line:
                painter.drawLine(points[1],points[2]);
                break;
            case Shape::_Rect:
                painter.drawRect(rect);
                break;
            case Shape::_RoundedRect:
                painter.drawRoundedRect(rect,40,40,Qt::RelativeSize);
                break;
            case Shape::_Polyline:
                painter.drawPolyline(points,4);
                break;
            case Shape::_Polygon:
                painter.drawPolygon(points,4);
                break;
            case Shape::_Ellipse:
                painter.drawEllipse(QRect(points[0],points[3]));
                //painter.drawEllipse(QPoint(40,40),30,30);
                //painter.drawEllipse(10, 20, 80, 60);
                break;
            case Shape::_Arc:
                painter.drawArc(rect,30*16,128*16);
                break;
            case Shape::_Pie:
                painter.drawPie(rect,25*16,100*16);
                break;
            case Shape::_Chord:
                painter.drawChord(rect,60*16,256*16);
                break;
            case Shape::_Path:
                painter.drawPath(path);
                break;
            case Shape::_Text:
                painter.drawText(rect,Qt::AlignCenter,"世界和平");
                break;
            case Shape::_Pixmap:
                painter.drawPixmap(QRectF(QPoint(2,2),QSize(512,512)),QPixmap(":/images/2-1.png"),QRectF(QPoint(2,2),QSize(512,512)));
                break;
            }
            painter.restore();
        }
    }

}

void PaintWidget::setShape(const Shape &shape)
{
    this->m_shape=shape;

    update();//会自动触发 绘画事件,paintevent
}
void PaintWidget::setPen(const QPen &pen)
{
    this->m_pen=pen ;
    update();
}

void PaintWidget::setBrush(const QBrush &brush)
{
    this->m_brush=brush;
    update();
}

void PaintWidget::setAntialias(const Qt::CheckState &status)
{
    this->m_status=status;
    update();
}

void PaintWidget::setMove_Tranfrom(const Qt::CheckState &status)
{
    this->m_move_transfrom=status;
    update();
}
