#include "widget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QStyle>

Widget::Widget(QWidget *parent)
    : FrameWidget(parent)
{
    initFrom();

    //功能函数,默认设置的都是true
    setonlyMovebyTitle(true);
    if(!canresized(true)){
        this->max_btn->hide();
    }


    setTitleWidget({title_widget,title_icon,title_text});
    //标题栏按键槽函数
    //窗口的状态改变会触发changeEvent事件
    connect(close_btn,&QPushButton::clicked,[&]{
        this->close();
    });
    connect(zoom_btn,&QPushButton::clicked,[&]{
        this->setWindowState(windowState()&~Qt::WindowActive|Qt::WindowMinimized);
    });
    connect(max_btn,&QPushButton::clicked,[&]{
        bool isnostate = this->windowState().testFlag(Qt::WindowNoState);
        bool ismaxstate = this->windowState().testFlag(Qt::WindowMaximized);
        bool isfullstate = this->windowState().testFlag(Qt::WindowFullScreen);

        if(ismaxstate||isnostate){    //不论是普通状态还是最大化，点击都会变成全屏
            this->setWindowState(Qt::WindowFullScreen);
            //this->showFullScreen();   //等价效果
        }
        if(isfullstate){  //当前是全屏状态
            if(exitfullscreen_status()){   //之前是不是最大化的
                this->setWindowState(Qt::WindowMaximized);
                //this->showMaximized();
            }
            else{
                this->setWindowState(Qt::WindowNoState);
            }

        }
    });
}

Widget::~Widget() {}

void Widget::changeEvent(QEvent *ev)
{

    if(ev->type()==QEvent::WindowStateChange){
        if(this->windowState().testFlag(Qt::WindowFullScreen)){
            max_btn->setFixedSize(36,36);
            max_btn->setStyleSheet("background-color: transparent;");
            max_btn->setIcon(QIcon(":/res/maxmin.svg"));
            max_btn->setCursor(QCursor(Qt::PointingHandCursor));
            //最小化键不能用
            zoom_btn->setEnabled(false);
            this->setAttribute(Qt::WA_TransparentForMouseEvents, true);//全屏状态，屏蔽掉了鼠标事件


        }
        else if(this->windowState().testFlag(Qt::WindowNoState)){
            max_btn->setFixedSize(36,36);
            max_btn->setStyleSheet("background-color: transparent;");
            max_btn->setIcon(QIcon(":/res/max.svg"));
            max_btn->setCursor(QCursor(Qt::PointingHandCursor));
            zoom_btn->setEnabled(true);
            this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        }
        //下面这个是应对，窗口最大化之后的样子
        else if(this->windowState().testFlag(Qt::WindowMaximized)){
            max_btn->setFixedSize(36,36);
            max_btn->setStyleSheet("background-color: transparent;");
            max_btn->setIcon(QIcon(":/res/max.svg"));
            max_btn->setCursor(QCursor(Qt::PointingHandCursor));
            zoom_btn->setEnabled(true);
            this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        }
    }
    QWidget::changeEvent(ev);
}

void Widget::initFrom()
{
    //设置初始的大小
    this->setMinimumSize(700,500);

    //窗口整体是垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    //标题栏
    title_widget=new QWidget(this);
    title_widget->setFixedHeight(40);
    title_widget->setStyleSheet("background-color: QLinearGradient(spread:reflect, x1:0, y1:1, x2:1, y2:1, stop:0.04 rgb(203,242,247),stop:0.96 rgb(255,248,213));");

    //标题栏加入整体布局中
    layout->addWidget(title_widget);
    //图标
    title_icon = new QLabel(title_widget);
    title_icon->setFixedSize(30,30);
    title_icon->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
    title_icon->setStyleSheet("background-color: transparent;");  //设置图标样式是透明的，避免和标题栏的背景色冲突
    title_icon->setPixmap(QPixmap(":/res/title.svg").scaled(30,30));
    //图标和标题之间的间隙
    QSpacerItem* space = new QSpacerItem(35,0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    //标题
    title_text = new QLabel(title_widget);
    title_text->setText("Ryan的百宝箱");
    title_text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    title_text->setStyleSheet(R"(
            background-color: rgba(255, 255, 255,0);
            font-size:18px ;
            font-family:"Hack Nerd Font";
            color:rgb(200,200,200);
            border:none
        )");

    // 默认地标签在水平方向和垂直方向的策略都是 Preferred。
    // 因此会自动将右侧的最小化/最大化/关闭按钮顶到右侧，不需要增加弹簧
    //最小窗口
    zoom_btn = new QPushButton(title_widget);
    zoom_btn->setFixedSize(36,36);
    zoom_btn->setStyleSheet("background-color: transparent");
    zoom_btn->setIcon(QIcon(":/res/zoom.svg"));
    zoom_btn->setCursor(QCursor(Qt::PointingHandCursor));
    //最大窗口
    max_btn = new QPushButton(title_widget);
    max_btn->setFixedSize(36,36);
    max_btn->setStyleSheet("background-color: transparent;");
    max_btn->setIcon(QIcon(":/res/max.svg"));
    max_btn->setCursor(QCursor(Qt::PointingHandCursor));
    //关闭窗口
    close_btn = new QPushButton(title_widget);
    close_btn->setFixedSize(36,36);
    close_btn->setStyleSheet("background-color: transparent;");
    close_btn->setIcon(QIcon(":/res/close.svg"));
    close_btn->setCursor(QCursor(Qt::PointingHandCursor));

    //标题栏内部是水平布局
    QHBoxLayout *titlelayout=new QHBoxLayout(title_widget);
    titlelayout->setSpacing(8);
    titlelayout->setContentsMargins(2,2,2,2);
    //标题栏内部控件加入到布局中
    titlelayout->addWidget(title_icon);
    titlelayout->addSpacerItem(space);
    titlelayout->addWidget(title_text);
    titlelayout->addWidget(zoom_btn);
    titlelayout->addWidget(max_btn);
    titlelayout->addWidget(close_btn);

    //主窗口
    main_widget=new QWidget(this);

    //设置背景色  QLinearGradient 线性渐变，x1 y1 左上角开始，x2 y2 右下角结束
    main_widget->setStyleSheet("background-color: QLinearGradient(spread:reflect, x1:0, y1:0, x2:0.5, y2:1, stop:0 #d5dee7,stop:0.5 #ffafbd,stop:1 #c9ffbf);");

    //主窗口布局
    QHBoxLayout *mainlayout=new QHBoxLayout(main_widget);
    mainlayout->setSpacing(20);

    //主窗口加入整体窗口
    layout->addWidget(main_widget);

    //主窗口按钮
    QPushButton* btn1 = new QPushButton("样式1",this);
    QPushButton* btn2 = new QPushButton("样式2",this);
    btn1->setFixedSize(100,100); //border-radius:50px; 圆角是前面大小的一半，为了设置成圆形的
    btn2->setFixedSize(100,100);
    QString style = R"(
                QPushButton{
                    background-color: QLinearGradient(spread:reflect, x1:1, y1:0, x2:0, y2:1, stop:0 #fff1eb,stop:1 #ace0f9);
                    font-size:16px;
                    font-family:"Hack Nerd Font";
                    color: rgb(99,98,84);
                    border: 5px ;
                    border-radius:50px;
                    padding: 14px
                }

                QPushButton:hover{
                    background-color: QLinearGradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #feada6,stop:1 #f5efef);
                }

                QPushButton:pressed{
                    background-color: QLinearGradient(spread:repeat, x1:0, y1:0, x2:0, y2:1, stop:0 #e9defa,stop:1 #fbfcdb);
                }
              )";

    btn1->setStyleSheet(style);
    btn2->setStyleSheet(style);

    //加入布局
    mainlayout->addWidget(btn1);
    mainlayout->addWidget(btn2);

    //绑定槽函数

    connect(btn1,&QPushButton::clicked,[&](){
        loadQss(":/qss/lightblue.css");
    });

    connect(btn2,&QPushButton::clicked,[&](){
        loadQss(":/qss/flatgray.css");
    });
}
