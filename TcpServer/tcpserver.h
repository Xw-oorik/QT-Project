#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpServer;
}
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private slots:
    void on_startbutton_clicked();

    void on_sendbutton_clicked();

private:
    Ui::TcpServer *ui;
    QTcpServer *server;
    QTcpSocket *socket;   //接受建立连接之后返回的socket
};
#endif // TCPSERVER_H
