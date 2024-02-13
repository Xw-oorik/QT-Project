#ifndef MYTASKS_H
#define MYTASKS_H

#include <QObject>
#include <QDebug>


class MyTasks : public QObject
{
    Q_OBJECT
public:
    explicit MyTasks(QObject *parent = nullptr);
    ~MyTasks();
public slots:
    void taskshow1();
    void taskshow2();

signals:
    void task1(int id);
};

#endif // MYTASKS_H
