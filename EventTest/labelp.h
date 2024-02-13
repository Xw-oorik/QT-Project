#ifndef LABELP_H
#define LABELP_H

#include <QLabel>
#include <QEvent>

class LabelP : public QLabel
{
    Q_OBJECT
public:
    explicit LabelP(QWidget *parent = nullptr);
protected:
    //鼠标进入，离开触发的事件
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    //鼠标按下，移动，释放触发的事件
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
signals:

};

#endif // LABELP_H
