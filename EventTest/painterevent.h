#ifndef PAINTEREVENT_H
#define PAINTEREVENT_H

#include <QWidget>
#include <QLabel>

class PainterEvent : public QWidget
{
    Q_OBJECT
public:
    explicit PainterEvent(QWidget *parent = nullptr);
private:
    bool eventFilter(QObject* watched, QEvent* event);
    void painthigh();
    void paintlow();
    void updateT();
private:
    QLabel *labhigh;
    QLabel *lablow;

    int highnum[14]{0};
    int lownum[14]{0};
signals:

};

#endif // PAINTEREVENT_H
