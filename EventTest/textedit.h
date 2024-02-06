#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);
private:
    void dropEvent(QDropEvent *e) override;  //拖动的文件再窗口或者控件中释放，触发
    void dragEnterEvent(QDragEnterEvent *e) override;//拖动文件进入，触发
    void dragLeaveEvent(QDragLeaveEvent *e) override;//文件离开，触发
    void dragMoveEvent(QDragMoveEvent *e) override;//移动，触发
    void wheelEvent(QWheelEvent *e) override; //滚轮

signals:

};

#endif // TEXTEDIT_H
