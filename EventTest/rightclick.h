#ifndef RIGHTCLICK_H
#define RIGHTCLICK_H

#include <QWidget>

class RightClick : public QWidget
{
    Q_OBJECT
public:
    explicit RightClick(QWidget *parent = nullptr);
protected:
    //可参考大丙老师，关于窗口右键菜单那一节
    void mousePressEvent(QMouseEvent *event) override; //鼠标事件完成
   void contextMenuEvent(QContextMenuEvent *event);//基于窗口的菜单策略完成
private slots:
    void righttrigger();
private:
    QAction *cnt;
    QAction *copy;
    QAction *hide;
signals:

};

#endif // RIGHTCLICK_H
