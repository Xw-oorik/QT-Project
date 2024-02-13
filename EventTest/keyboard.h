#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLabel>

class KeyBoard : public QWidget
{
    Q_OBJECT
public:
    explicit KeyBoard(QWidget *parent = nullptr);
private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QLabel *qls;
signals:

};

#endif // KEYBOARD_H
