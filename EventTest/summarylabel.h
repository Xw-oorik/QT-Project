#ifndef SUMMARYLABEL_H
#define SUMMARYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
class SummaryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SummaryLabel(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);
signals:

};

#endif // SUMMARYLABEL_H
