#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{}

MyThread::~MyThread()
{
    qDebug()<<"MyThread 资源回收完毕";
}

void MyThread::run()
{

    qDebug()<<"cpu:"<<this->idealThreadCount ();

    qDebug()<<"running ! ";
    int id=0;
    for(;;){

        qDebug()<<id;
        emit passbynum (id++);

        if(id>10){
            break;
        }
        sleep (1);

    }
    //exec();  事件循环
    qDebug()<<"running over !";
}
