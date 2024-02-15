#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    this->setWindowTitle("TcpServer");

    server = new QTcpServer(this);
    socket = new QTcpSocket();

    ui->sendbutton->setEnabled(false);  //默认刚开始不能发数据

    connect(server,&QTcpServer::newConnection,this,[&](){ //建立新连接
        socket = server->nextPendingConnection();

        QString str =QString("server connect with [client:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        ui->textBrowser_2->append(str);
        ui->sendbutton->setEnabled(true);

        //检测有无客户端数据
        connect(socket,&QTcpSocket::readyRead,this,[&](){
            QString recvdata = socket->readAll();
            ui->textBrowser->append("client:"+recvdata);
        });
        //检测连接是否断开
        connect(socket,&QTcpSocket::disconnected,this,[&](){
            ui->textBrowser_2->append("servershow:server断开连接");
            if(server->isListening()){
                ui->textBrowser_2->append("连接断开，server仍再监听");
            }
            else{
                ui->textBrowser_2->append("server没有监听");
            }
            ui->sendbutton->setEnabled(false); //不能发送数据
        });
    });
}

TcpServer::~TcpServer()
{
    delete ui;
    //不需要下面的,因为server挂载到对象树和close源码，解析看我博客对应篇章
    //server->close();
    //server->deleteLater();
}

void TcpServer::on_startbutton_clicked()
{
    if(ui->portedit->text().isEmpty()){
        ui->textBrowser_2->append("请输入监听端口！");
        return ;
    }

    quint16 port = static_cast<quint16>(ui->portedit->text().toUInt());
    if(ui->startbutton->text()=="启动服务器"){

        if(!server->listen(QHostAddress::Any,port)){
            QString errnr = server->errorString();
            ui->textBrowser_2->append(errnr);
            return ;
        }
        QString ip = server->serverAddress().toString();
        QString str_port = QString::number(port);
        QString listen_str = "server:"+ip+"  "+"port:"+str_port+" "+"正在监听中...";
        ui->textBrowser_2->append(listen_str);
        ui->startbutton->setText("关闭服务器");
    }
    else{
        if(server->hasPendingConnections()){//如果服务器正在监听，并且有一个或多个挂起的连接请求

            socket->abort();//中止当前连接并重置Socket。会立即关闭Socket，丢弃写入缓冲区中的任何挂起数据。
        }
        if(server->isListening()){
            ui->textBrowser_2->append("startbutton server 正在监听连接");
            socket->abort();  //转到&QTcpSocket::disconnectet
        }
        else{
            ui->textBrowser_2->append("startbutton server 没有监听");
        }
        server->close();//关闭服务器，不再监听
        ui->textBrowser_2->append("server断开监听，关闭现有连接");
        ui->startbutton->setText("启动服务器");

    }

}

void TcpServer::on_sendbutton_clicked()
{
    QString send_Msg = ui->textEdit->toPlainText();
    socket->write(send_Msg.toUtf8());
    socket->waitForBytesWritten();
    ui->textEdit->clear();
    ui->textBrowser->append("server: "+send_Msg);
}

