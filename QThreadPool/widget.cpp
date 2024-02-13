#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    task = new Task;
    qDebug()<<"maxThreadCount: "<<QThreadPool::globalInstance()->maxThreadCount();


    connect(ui->pushButton,&QPushButton::clicked,ui->lcdNumber,[&]{
         QThreadPool::globalInstance()->start(task);//拿到全局的pool
    });

    connect(task,&Task::tasks,this,[=](int id){
        ui->lcdNumber->display(QString::number(id));
    });

}

Widget::~Widget()
{
    delete ui;
}
