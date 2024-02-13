#ifndef MOUSEPRESSMOVEREALSE_H
#define MOUSEPRESSMOVEREALSE_H

#include <QWidget>
#include <QLabel>
class MousePressMoveRealse : public QWidget
{
    Q_OBJECT
public:
    explicit MousePressMoveRealse(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject* watched,QEvent* event);

private:
    QLabel *qls;
    QWidget *ws;
    QPoint presspos; //鼠标位置
    QPoint labelpos;  //标签位置
signals:

};

#endif // MOUSEPRESSMOVEREALSE_H
