#include "framewidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStyle>

FrameWidget::FrameWidget(QWidget *parent)
    : QWidget{parent}
{

    //去除标题栏
    this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);//设置透明

    location = Location::CENTER;
    this->installEventFilter(this);

}

void FrameWidget::setTitleWidget(QVector<QWidget *> widgets)
{
    title_widgets = widgets;
}

void FrameWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        isleft_pressed = true;
        winPos = this->pos();
        pressPos = event->globalPos();
        //判断左键按下的位置在不在标题栏中
        QWidget *currentwidget = QApplication::widgetAt(pressPos);
        if(currentwidget){
            foreach (QWidget *ws, title_widgets) {
                if(ws==currentwidget){
                    isleft_pressed_intitle = true;
                    break;
                }
            }
        }
    }
    else{
        return ;
    }
}

void FrameWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint globalpos = event->globalPos(); //全局坐标
    if(!isleft_pressed){ //左键未按下
        if(this->windowState().testFlag(Qt::WindowNoState)&&can_resized){
            setCursorShape(globalpos);
        }
        return ;
    }

    //左键按下了
    //缩放

    if(location!=Location::CENTER){
        QRect rect =this->rect();
        QPoint topLeft = mapToGlobal(rect.topLeft());
        QPoint bottomRight = mapToGlobal(rect.bottomRight());

        QRect rMove(topLeft, bottomRight);
        switch (location) {
        case Location::TOP:
            if(bottomRight.y()-globalpos.y()>this->minimumHeight()){
                rMove.setY(globalpos.y());
            }
            break;
        case Location::BOTTOM:
            rMove.setHeight(globalpos.y()-topLeft.y());
            break;
        case Location::LEFT:
            if(bottomRight.x()-globalpos.x()>this->minimumWidth()){
                rMove.setX(globalpos.x());
            }
            break;
        case Location::RIGHT:
            rMove.setWidth(globalpos.x()-topLeft.x());
            break;
        case Location::TOP_LEFT:
            if ( bottomRight.y() - globalpos.y() > this->minimumHeight() ) {
                rMove.setY(globalpos.y());
            }
            if(bottomRight.x()-globalpos.x()>this->minimumWidth()){
                rMove.setX(globalpos.x());
            }
            break;
        case Location::TOP_RIGHT:
            if(bottomRight.y()-globalpos.y()>this->minimumHeight()){
                rMove.setY(globalpos.y());
            }
            rMove.setWidth(globalpos.x()-topLeft.x());
            break;
        case Location::BOTTOM_LEFT:
            rMove.setHeight(globalpos.y()-topLeft.y());
            if(bottomRight.x()-globalpos.x()>this->minimumWidth()){
                rMove.setX(globalpos.x());
            }
            break;
        case Location::BOTTOM_RIGHT:
            rMove.setHeight(globalpos.y()-topLeft.y());
            rMove.setWidth(globalpos.x()-topLeft.x());
            break;
        default:
            break;
        }
        this->setGeometry(rMove);
    }
    //移动
    else{
        if(isleft_pressed_intitle){  //在标题栏按下
            if(this->isMaximized()){ //如果是最大的，拖动标题栏会返回缩小到原来状态
                //拿到鼠标相对于窗口的百分比
                float width_ration = float(event->globalPos().x())/float(this->width());
                    //窗口回到原位
                this->setWindowState(Qt::WindowNoState);
                //鼠标相对位置不变
                int offset = this->width()*width_ration;
                winPos.setX(event->globalPos().x()-offset);  //建议画图，理解这几段代码
                winPos.setY(0);
            }
            else{
                this->move(winPos+(event->globalPos()-pressPos));
            }

        }
        else {  //非标题栏处按下
            if(!only_move_by_title&&!this->isMaximized()){
                this->move(winPos+(event->globalPos()-pressPos));
            }
        }

    }


}

void FrameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isleft_pressed = false;
    isleft_pressed_intitle = false;
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void FrameWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    //判断双击的位置在不在标题栏中
    if(can_resized){
        QWidget *currentwidget = QApplication::widgetAt(event->globalPos());
        if(currentwidget){
            bool intitle{false};
            foreach (QWidget *ws, title_widgets) {
                if(ws==currentwidget){
                    intitle = true;
                    break;
                }
            }
            if(intitle){
                if(this->isMaximized()){
                    this->setWindowState(Qt::WindowNoState);
                    exitfull_screen_status = false;   //记录全屏前的状态
                }
                else{
                    this->setWindowState(Qt::WindowMaximized);
                    exitfull_screen_status = true;
                }
            }
        }
    }
    return ;

}

bool FrameWidget::exitfullscreen_status()
{
    return exitfull_screen_status;
}

void FrameWidget::setAllWidgetMouseTracking(QWidget* widget)
{
    this->setMouseTracking(true);//鼠标跟踪是指鼠标在窗口中的移动会被捕捉并触发相应的事件

    QObjectList chids = widget->children();
    foreach (QObject* cs, chids) {
        if(cs->metaObject()->className()==QStringLiteral("QWidget")){
            QWidget* obj = qobject_cast<QWidget*>(cs);
            obj->setMouseTracking(true);

            setAllWidgetMouseTracking(obj);
        }

    }
}

/* 当前窗口绘制时，给窗口中的所有控件设置鼠标追踪。
 * 这样鼠标在移动到边界时，可以追踪得到，从而设置光标为缩放形状
 */
bool FrameWidget::eventFilter(QObject *target, QEvent *event)
{
    if(event->type()==QEvent::Paint){
        static bool init = false;
        if(!init){
            init = true;
            setAllWidgetMouseTracking(this);
        }
    }

    return QWidget::eventFilter(target,event);
}

void FrameWidget::setCursorShape(const QPoint &point)
{
    //拿到窗口矩形，相对于全局窗口的 左上角，右下角
    QRect winrect = this->rect();
    QPoint top_left = mapToGlobal(winrect.topLeft());
    QPoint bottom_right = mapToGlobal(winrect.bottomRight());

    int x = point.x();  //也是全局坐标
    int y = point.y();
    //左上，左下，右上，右下
    if((x>=top_left.x()&&x<top_left.x()+PADDING)&&(y>=top_left.y()&&y<top_left.y()+PADDING)){
        location = Location::TOP_LEFT;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if((x>=top_left.x()&&x<top_left.x()+PADDING)&&(y>=bottom_right.y()-PADDING&&y<bottom_right.y())){
        location = Location::BOTTOM_LEFT;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if((x>=bottom_right.x()-PADDING&&x<bottom_right.x())&&(y>=top_left.y()&&y<top_left.y()+PADDING)){
        location = Location::TOP_RIGHT;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if((x>=bottom_right.x()-PADDING&&x<bottom_right.x())&&(y>bottom_right.y()-PADDING&&y<=bottom_right.y())){
        location = Location::BOTTOM_RIGHT;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    //上下左右
    else if(y>=top_left.y()&&y<=top_left.y()+PADDING){
        location = Location::TOP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if(y>=bottom_right.y()-PADDING&&y<=bottom_right.y()){
        location = Location::BOTTOM;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if(x>=top_left.x()&&x<=top_left.x()+PADDING){
        location = Location::LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(x>=bottom_right.x()-PADDING&&x<=bottom_right.x()){
        location = Location::RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }

    else {
        location = Location::CENTER;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

bool FrameWidget::setonlyMovebyTitle(bool only_move_by_title)
{
    return (this->only_move_by_title = only_move_by_title);

}

bool FrameWidget::canresized(bool can_resized)
{
    return (this->can_resized = can_resized);
}

void FrameWidget::loadQss(const QString &qss_str)
{
    // 清除所有子控件的样式
    for (QWidget *child : this->findChildren<QWidget*>()) {
        style()->unpolish(this);
        child->setStyleSheet("");
    }
    QString qss;
    QFile file(qss_str);
    if (file.open(QFile::ReadOnly)) {
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        //in.setCodec("utf-8");
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        file.close();
        qss = list.join("\n");
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(paletteColor));
        //用时主要在下面这句
        qApp->setStyleSheet(qss);
    }
}
