#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置背景板只读
    ui->backgroudcolor->setReadOnly(true);
    //设置最大最小值
    ui->redspl_2->setMinimum(0);
    ui->redspl_2->setMaximum(255);
    ui->greenspl->setRange(0,255);
    ui->bluespl->setRange(0,255);
    //设置步长，键盘左右的步长和鼠标点击滑块的步长
    ui->redspl_2->setSingleStep(2);
    ui->redspl_2->setSingleStep(5);
    ui->greenspl->setSingleStep(3);
    ui->greenspl->setSingleStep(7);
    ui->bluespl->setSingleStep(5);
    ui->bluespl->setSingleStep(10);
    //给背景板和显示数值给默认值
    setcolor();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setcolor() //把随着滑动条移动，数字和背景色改变抽象出来
{
    QString redval=QString::number(ui->redspl_2->value());
    QString greenval=QString::number(ui->greenspl->value());
    QString blueval=QString::number(ui->bluespl->value());
    ui->redline->setText(redval);
    ui->greenline->setText(greenval);
    ui->blueline->setText(blueval);
    ui->backgroudcolor->setStyleSheet("background-color: rgb("+redval+","+greenval+","+blueval+","+");");
}

//下面是直接在ui界面，控件转到槽了，所以不用我们手动connect了

void Widget::on_redspl_2_valueChanged(int value)
{
    setcolor();
}

void Widget::on_bluespl_valueChanged(int value)
{
    setcolor();
}

void Widget::on_greenspl_valueChanged(int value)
{
    setcolor();
}
