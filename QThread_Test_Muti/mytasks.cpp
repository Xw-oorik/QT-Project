#include "mytasks.h"
#include "unistd.h"

MyTasks::MyTasks(QObject *parent)
    : QObject{parent}
{}

MyTasks::~MyTasks()
{
    qDebug()<<"task over 资源释放";
}

void MyTasks::taskshow1()
{
    qDebug()<<"taskshow1 run";

    int id=0;
    while(1){
        qDebug()<<id;
        emit task1 (id++);

        if(id>10){
            break;
        }
        sleep (1);
    }
    qDebug()<<"taskshow1 over";
}

void MyTasks::taskshow2()
{
    qDebug()<<"taskshow2 run";

    int id=10;
    while(1){
        qDebug()<<id;
        emit task1 (id++);

        if(id>20){
            break;
        }
        sleep (1);
    }
    qDebug()<<"taskshow2 over";
}
