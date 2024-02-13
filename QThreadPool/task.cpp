#include "task.h"
#include "unistd.h"
#include <QDebug>

Task::Task(QObject *parent)
    : QObject{parent}
{

    this->setAutoDelete(true);  //任务自动析构

}

void Task::run()
{
    int id=0;

    while(1){
        qDebug()<<id;
        emit tasks(id++);

        if(id>10){
            break;
        }
        sleep(1);
    }
}
