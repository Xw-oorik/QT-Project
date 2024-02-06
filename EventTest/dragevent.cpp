#include "dragevent.h"
#include <QVBoxLayout>
#include <QLabel>
#include "textedit.h"

//  拖动事件
DragEvent::DragEvent(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->setSpacing(0);
    vblayout->setContentsMargins(0,10,0,10);

    QLabel *ql = new QLabel(this);
    ql->setText("拖动事件");
    ql->setFixedHeight(50);
    ql->setFrameShape(QFrame::Box);
    ql->setAlignment(Qt::AlignCenter);
    ql->setStyleSheet("color:green;font:25px;background-color:rgb(0,233,233);border-radius:10px;"
                      );
    vblayout->addWidget(ql);

    //textedit
    TextEdit *ts= new TextEdit(this);
    ts->setPlaceholderText("请拖动文件，文件内容会显示在窗口");//用来设置占位文字吗，lineedit也有
    vblayout->addWidget(ts);


}
