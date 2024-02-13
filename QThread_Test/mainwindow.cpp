#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread = new MyThread(this);

    connect (thread,&MyThread::passbynum ,this,[=](int id){
        ui->lcdNumber->display (QString ::number (id));
    });

}

MainWindow::~MainWindow()
{
    //没有调用exit或者quit，他们的作用都是退出线程，停止对应的事件循环
    //如果thread没有开启事件循环比如，在run里面没有调exec，这里就不用exit或者quit

    //thread->exit ();
    thread->wait ();//等着子线程执行完
    delete ui;

    //因为 thread = new MyThread(this); 绑在对象树上了
    //最后这不需要delete thread，，没有绑定就需要

    qDebug()<<"MainWindow over";
}




void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"clicked  thread start!";

    thread->start ();

}

