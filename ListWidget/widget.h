#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QListWidgetItem>
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
    void oncheck(bool checked);

    void currentitemClicked(QListWidgetItem *item);
     void currentDoubleitemClicked(QListWidgetItem *item);
    void Additem();
    void Insertitem();
    void Deleteitem();
private:
    Ui::Widget *ui;
    QButtonGroup* btngroup;

};
#endif // WIDGET_H
