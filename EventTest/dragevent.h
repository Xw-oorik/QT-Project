#ifndef DRAGEVENT_H
#define DRAGEVENT_H

#include <QWidget>

class DragEvent : public QWidget
{
    Q_OBJECT
public:
    explicit DragEvent(QWidget *parent = nullptr);

signals:

};

#endif // DRAGEVENT_H
