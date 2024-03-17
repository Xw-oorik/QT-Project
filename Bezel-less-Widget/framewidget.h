#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>


#define PADDING 4    //边界像素
enum class Location : char {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOP_LEFT,
    BOTTOM_LEFT,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    CENTER
};

class FrameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FrameWidget(QWidget *parent = nullptr);

protected:
    void setTitleWidget(QVector<QWidget*> widgets); //存标题栏里面的控件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);  //双击把屏幕最大化（注意不是全屏）

    //记录全屏要缩小的时候，全屏前的状态，如果全屏前是放大的，那么就恢复放大状态
    bool exitfullscreen_status();

    // 用于设置鼠标追踪
    void setAllWidgetMouseTracking(QWidget* widget); //窗口重新绘制时，需要递归的给窗口内所有控件设置鼠标追踪
    bool eventFilter(QObject* target, QEvent* event);
    //设置鼠标追踪到边界的形状
    void setCursorShape(const QPoint& point);
protected:
    //提供两个功能函数
    //只能用标题栏去拖动窗口
    bool setonlyMovebyTitle(bool only_move_by_title);
    //是否可以缩放窗口
    bool canresized(bool can_resized);
    //加载qss
    void loadQss(const QString &qss_str);
private:
    bool exitfull_screen_status{false}; //记录双击标题栏之后的窗口状态，在窗口从最大化变成全屏，再从全屏变回去的时候判断用
private:
    bool isleft_pressed{false};  //左键是否按下
    bool isleft_pressed_intitle{false}; //判断是否在标题栏里面 按下
    QVector<QWidget*> title_widgets;
    QPoint pressPos; //按下的位置
    QPoint winPos; //窗口的位置
    Location location;// 判断边界位置的
private:
    bool only_move_by_title{true};
    bool can_resized{true};
signals:

};

#endif // FRAMEWIDGET_H
