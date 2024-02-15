#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("TcpClient");

    socket = new QTcpSocket(this);
    ui->senddata->setEnabled(false);  //默认先不能发数据

    //检测是否成功建立连接
    connect(socket,&QTcpSocket::connected,this,[&](){
        QString str =QString("client connect with [client:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        ui->textBrowser_2->append(str);
        ui->senddata->setEnabled(true);
        ui->startconnect->setEnabled(false);
        ui->Disconnect->setEnabled(true);
    });


    //检测有无服务端数据
    connect(socket,&QTcpSocket::readyRead,this,[&](){
        QString recvdata = socket->readAll();
        ui->textBrowser->append("server:"+recvdata);
    });

    //检测连接是否断开
    connect(socket,&QTcpSocket::disconnected,this,[&](){
        ui->textBrowser_2->append("clientshow:client断开连接");
        ui->senddata->setEnabled(false);
        ui->startconnect->setEnabled(true);
        ui->Disconnect->setEnabled(false);
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startconnect_clicked()
{
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
        ui->textBrowser_2->append("请输入服务器ip/主机名 | port ！");
        return ;
    }

    QString ip = ui->lineEdit->text();
    quint16 port = static_cast<quint16>(ui->lineEdit_2->text().toUInt());

    qDebug()<<socket->state() ;

    if(socket->state() == QAbstractSocket::ConnectedState){//多次按下的时候
        socket->disconnectFromHost();
        socket->waitForDisconnected();
    }

    qDebug()<<socket->state() ;

    socket->connectToHost(ip,port);

    qDebug()<<socket->state() ;

    if(socket->state() == QAbstractSocket::ConnectingState){
        ui->textBrowser_2->append("开启建立连接...");
    }

    bool flg = socket->waitForConnected(); //默认30s
    if(!flg){
        if(socket->state() == QAbstractSocket::UnconnectedState){
            ui->textBrowser_2->append("state:UnconnectedState-- "+socket->errorString());
        }
        if (socket->error() == QAbstractSocket::SocketTimeoutError) {
            ui->textBrowser_2->append("Connection timed out") ;
        }
        else if(socket->error() == QAbstractSocket::HostNotFoundError){
            ui->textBrowser_2->append("can not find ip") ;
        }
    }
    else{
        if(socket->state() == QAbstractSocket::ConnectedState){
            ui->textBrowser_2->append("已建立连接...");

            switch (socket->socketType()) {
            case QAbstractSocket::TcpSocket:
                ui->textBrowser_2->append("protocol：TCP");
                break;
            case QAbstractSocket::UdpSocket:
                ui->textBrowser_2->append("protocol：UDP");
                break;
            case QAbstractSocket::SctpSocket:
                ui->textBrowser_2->append("protocol：SCTP");
                break;
            default:
                ui->textBrowser_2->append("UnknownSocketType");
                break;
            }
        }
    }

}


void Widget::on_Disconnect_clicked()
{
    if(ui->startconnect->isEnabled()){
        qDebug()<<socket->state() ;

        ui->textBrowser_2->append("The server or port is not starting or listening");
    }
    else{
        qDebug()<<socket->state() ;

        socket->disconnectFromHost();
        socket->waitForDisconnected();
    }

    qDebug()<<socket->state() ;
}


void Widget::on_senddata_clicked()
{
    QString send_Msg = ui->textEdit->toPlainText();

    socket->write(send_Msg.toUtf8());
    socket->waitForBytesWritten();
    ui->textEdit->clear();
    ui->textBrowser->append("client: "+send_Msg);

}

