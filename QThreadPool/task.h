#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QRunnable>

class Task : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    void run()override;

signals:
    void tasks(int id);
};

#endif // TASK_H
