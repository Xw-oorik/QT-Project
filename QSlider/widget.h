#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void setcolor();
private slots:
    void on_redspl_2_valueChanged(int value);

    void on_bluespl_valueChanged(int value);

    void on_greenspl_valueChanged(int value);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
