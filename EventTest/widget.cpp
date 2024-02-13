#include "widget.h"
#include "dragevent.h"
#include "keyboard.h"
#include "mouse_in_leave.h"
#include "mouse_press_move_realse.h"
#include "painterevent.h"
#include "rightclick.h"
#include "summaryevent.h"
#include "timerevent.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //整体是水平布局
    QHBoxLayout *holelayout = new QHBoxLayout(this);
    holelayout->setSpacing(0);
    holelayout->setContentsMargins(0,0,0,0);
    //左侧垂直布局
    navWidget=new QWidget(this);
    QVBoxLayout *leftlayout= new QVBoxLayout(navWidget);
    leftlayout->setSpacing(0);
    leftlayout->setContentsMargins(0,0,0,0);
    holelayout->addWidget(navWidget);
    //右侧垂直布局
    mainWidget=new QWidget(this);
    mainWidget->setMinimumWidth(400);
    QVBoxLayout *rightlayout= new QVBoxLayout(mainWidget);
    rightlayout->setSpacing(0);
    rightlayout->setContentsMargins(5,5,5,5);
    stackWidget = new QStackedWidget(mainWidget);
    rightlayout->addWidget(stackWidget);
    holelayout->addWidget(mainWidget);

    //导航栏初始化
    InitNavigation();
    //页面初始化
    InitMainWidget();
}

Widget::~Widget()
{
}

void Widget::InitNavigation()
{
    QStringList names;
    names<<"鼠标进入/离开"<<"鼠标按下/移动/释放"
        <<"键盘事件"<<"定时器事件"<<"拖动事件"
       <<"绘图事件"<<"右键菜单"<<"summary";

    btngp=new QButtonGroup(this);
    //生成按钮
    for(int i=0;i<names.count();++i)
    {
        QPushButton *tmpbutton =new QPushButton;

        tmpbutton->setMinimumHeight(42);
        tmpbutton->setText(QString("%1.%2").arg(i+1,2,10,QChar('0')).arg(names.at(i)));
        //设置按钮可选中,就是按了之后不弹起来
        tmpbutton->setCheckable(true);
        //给每一个按钮和页面把信号槽绑定起来
        connect(tmpbutton,&QPushButton::clicked,this,&Widget::tt);
        //设置样式表
        tmpbutton->setStyleSheet(R"(
            QPushButton {
                font: 20px;
                text-align:left;
                color: #ffffff;
                background-color: #336699;
                margin: 10px;
                padding: 10px;
            })");

        btngp->addButton(tmpbutton,i);
        navWidget->layout()->addWidget(tmpbutton);
    }
    //默认设置第一个页面，按钮显示
    btngp->button(0)->click();

}

void Widget::InitMainWidget()
{

    stackWidget->addWidget(new MouseInLeave());
    stackWidget->addWidget(new MousePressMoveRealse());

    stackWidget->addWidget(new KeyBoard());
    stackWidget->addWidget(new TimerEvent());
    stackWidget->addWidget(new DragEvent());
    stackWidget->addWidget(new PainterEvent());
    stackWidget->addWidget(new RightClick());

    stackWidget->addWidget(new SummaryEvent());


}

void Widget::tt()
{
    int id = btngp->checkedId();
    stackWidget->setCurrentIndex(id);
}

