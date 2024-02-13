    #include "widget.h"
    #include "ui_widget.h"

    Widget::Widget(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Widget)
    {
        ui->setupUi(this);

        tak1 = new MyTasks;
        tak2 = new MyTasks;
        th1 = new QThread(this);
        th2 = new QThread(this);

        tak1->moveToThread(th1);
        tak2->moveToThread(th2);

        th1->start();
        th2->start();

        connect(ui->pushButton,&QPushButton::clicked,tak1,&MyTasks::taskshow1);
        connect(ui->pushButton,&QPushButton::clicked,tak2,&MyTasks::taskshow2);


        connect(tak1,&MyTasks::task1,this,[=](int id){
            ui->label->setText(QString::number(id));
        });

        connect(tak2,&MyTasks::task1,this,[=](int id){
            ui->label_2->setText(QString::number(id));
        });
    }

    Widget::~Widget()
    {

        th1->exit();
        th1->wait();
        qDebug()<<"th1 over";

        th2->exit();
        th2->wait();
        qDebug()<<"th2 over";

        delete tak1;
        delete tak2;

        delete ui;
        qDebug()<<"Widget over";
    }

