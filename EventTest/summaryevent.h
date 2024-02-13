#ifndef SUMMARYEVENT_H
#define SUMMARYEVENT_H
#include "summarylabel.h"
#include <QWidget>

class SummaryEvent : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryEvent(QWidget *parent = nullptr);
private:
    SummaryLabel *ql;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event);
signals:

};

#endif // SUMMARYEVENT_H
