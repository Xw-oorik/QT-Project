#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
//C++11 枚举类
enum class Shape{

    _Point,
    _Line,         //

    _Rect,          //
    _RoundedRect,   //
    _Ellipse,       //

    _Polyline,      //
    _Polygon,       //

    _Arc,           //
    _Pie,           //
    _Chord,         //

    _Path,          //

    _Text,          //
    _Pixmap

};

//就是中间那个用来绘图的widget，我们ui创建widget之后给这个widget提升成这个PaintWidget
class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialias(const Qt::CheckState &status );
    void setMove_Tranfrom(const Qt::CheckState &status);
protected:
    void paintEvent(QPaintEvent *event) override;
public slots:
    void setShape(const Shape& shape);
private:
    Shape m_shape;
    QPen m_pen;
    QBrush m_brush;
    Qt::CheckState m_status;
    Qt::CheckState m_move_transfrom;
signals:

};

#endif // PAINTWIDGET_H
