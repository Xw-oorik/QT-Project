#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QTableWidgetItem>
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
    void appendOneRow(QString name,int age,QString sex,QString province);
    void appsettings();
    void choosesettings();
    void datamanipulation();
public slots:;
    void choseradio();
    void showtest(QTableWidgetItem *item);
private:
    Ui::Widget *ui;
    QButtonGroup *mbtg; //对于radio的选择使用，一般都是绑定一个QButtonGroup
};
#endif // WIDGET_H
