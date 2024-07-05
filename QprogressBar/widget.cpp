#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置定时器
    m_timedownload=new QTimer(this);
    m_timedownload->setInterval(50);

    m_timecopy=new QTimer(this);
    m_timecopy->setInterval(20);

    //设置下载的进度在左边
    ui->download->setAlignment(Qt::AlignLeft);
    //设置拷贝的进度格式  ,最大最小值
    ui->kaobei->setFormat(QString("%v/%m"));
    ui->kaobei->setRange(0,500);

    //设置网络传输进度条一直不变 ,可以达到循环不变的效果
    ui->chuanshu->setRange(0,0);

    //信号槽连接
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::downloadtimeout);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::copyloadtimeout);

    connect(m_timedownload,&QTimer::timeout,this,&Widget::downloadchange);
    connect(m_timecopy,&QTimer::timeout,this,&Widget::copychange);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::downloadtimeout()
{
    ui->download->reset();
    m_timedownload->start();
}

void Widget::copyloadtimeout()
{
    ui->kaobei->reset();
    m_timecopy->start();
}

void Widget::downloadchange()
{
    int current = ui->download->value();
    if(current == ui->download->maximum()){
        m_timedownload->stop();
        QMessageBox::information(this,"提示","文件下载完成");
    }
    else{
        ui->download->setValue(current+1);
    }

}

void Widget::copychange()
{
    int current = ui->kaobei->value();
    if(current == ui->kaobei->maximum()){
        m_timecopy->stop();
        QMessageBox::information(this,"提示","文件拷贝完成");
    }
    else{
        ui->kaobei->setValue(current+1);
    }
}

