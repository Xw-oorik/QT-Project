#include "textedit.h"
#include <QDebug>
#include <QMimeData>
#include <QApplication>
TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
     this->setAcceptDrops(true); //允许接受drop事件
}

void TextEdit::dropEvent(QDropEvent *e)
{
    qDebug()<<"dropEvent";
    if(!e->mimeData()->hasUrls()){
        return ;
    }
    QList<QUrl> urls=e->mimeData()->urls();
    for(auto ll:urls){
        qDebug()<<"urls::"<<ll.toString();
    }

    QString filename=urls.first().toLocalFile();
    qDebug()<<urls.first()<<"."<<filename;

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        setPlainText(file.readAll());
        file.close();
    }


}

void TextEdit::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug()<<"dragEnterEvent";
     // 默认情况下,窗口部件是不接受拖动的。,需要加这个函数
    e->acceptProposedAction();
}

void TextEdit::dragLeaveEvent(QDragLeaveEvent *e)
{
    qDebug()<<"dragLeaveEvent";
}

void TextEdit::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug()<<"dragMoveEvent";
}

void TextEdit::wheelEvent(QWheelEvent *e)
{
    if(QApplication::keyboardModifiers()==Qt::ControlModifier)
    {
        if(e->delta()>0){
            this->zoomIn();//放大
        }
        else{
            this->zoomOut();//缩小
        }
    }
    else{
        QTextEdit::wheelEvent(e);

    }
}
