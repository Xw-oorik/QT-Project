#ifndef MOUSEINLEAVE_H
#define MOUSEINLEAVE_H

#include <QWidget>
#include <QLabel>
#include <QEvent>

class MouseInLeave : public QWidget
{
    Q_OBJECT
public:
    explicit MouseInLeave(QWidget *parent = nullptr);
private:
    bool eventFilter(QObject* watched, QEvent *event);
private:
    QLabel *qls;
signals:

};

#endif // MOUSEINLEAVE_H
