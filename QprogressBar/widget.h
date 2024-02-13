#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void downloadtimeout();
    void copyloadtimeout();

    void downloadchange();
    void copychange();

private:
    Ui::Widget *ui;
    QTimer *m_timedownload;
    QTimer *m_timecopy;


};
#endif // WIDGET_H
