#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置最大值，最小值
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(100);

    ui->doubleSpinBox->setRange(1.00,250.00);
    //设置步长
    ui->doubleSpinBox->setSingleStep(0.01);//一次增加多少
    //设置循环，就是增加到最大值之后，再增加会重置
    ui->spinBox->setWrapping(true);

    //设置加速
    ui->doubleSpinBox->setAccelerated(true);
    //设置前缀，后缀的显示
    ui->spinBox->setSuffix(QString(" kg"));
    ui->doubleSpinBox->setPrefix(QString("$"));

    //绑定信号槽
    //这里直接在ui界面点击的对应控件，直接转到信号槽，自动生成了
    //所以不需要我们手动再connect了
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_spinBox_valueChanged(int arg1)
{
    double val=ui->doubleSpinBox->value();

    double res=arg1*val;

    QString tx=QString::number(res);
    ui->resedit->setText(tx);
}

void Widget::on_doubleSpinBox_valueChanged(double arg1)
{
    int kg=ui->spinBox->value();

    double res=kg*arg1;

    QString tx=QString::number(res);
    ui->resedit->setText(tx);
}
