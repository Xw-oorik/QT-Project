#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <weatherdata.h>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event)override;
    //http请求
    void sendrequest(const QString &code);

    void parseJson( QByteArray &array);//响应的 解析json，填充到weatherdata的类

    void updateUI();  //更新界面ui

    void drawhigh();//绘制高温曲线
    void drawlow();
    void updateT();  //城市改变，曲线重新绘制
private slots:
    void onReply(QNetworkReply *reply);
    void Serachcity();
private:
    QNetworkAccessManager *m_manger;
    Today m_today;
    Day m_week[6];

    Ui::MainWindow* ui;

    QMenu* mExitMenu;   // 右键退出的菜单
    QAction* mExitAct;  // 退出的行为
    QPoint m_offset; //偏移

    //存图标或者label的
    //星期和日期
    QList<QLabel*> m_weeklist;
    QList<QLabel*> m_datelist;
    //天气和天气图标
    QList<QLabel*> m_typelist;
    QList<QLabel*> m_typeiconlist;
    //污染指数
    QList<QLabel*> m_aqilist;
    //风力进而风向
    QList<QLabel*> m_fxlist;
    QList<QLabel*> m_fllist;

    //存图标
    QHash<QString,QString> m_pixmap;
};
#endif  // MAINWINDOW_H
