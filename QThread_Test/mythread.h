#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();
protected:
    void run() override;

signals:
    void passbynum(int id);
};

#endif // MYTHREAD_H
