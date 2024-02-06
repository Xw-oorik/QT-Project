#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加省份
    ui->province_comboBox->addItem("四川");
    QStringList provices{"陕西","浙江"};
    ui->province_comboBox->insertItems(1,provices);

    //添加城市
    addcitys();

    //省份和城市对应，省份改变，城市集合改变
    //因为QComboBox::currentIndexChanged 有重载版本，所以要用函数指针去和重载版本去区分
    void (QComboBox::*qcomboxsignal)(int)=&QComboBox::currentIndexChanged;

    void (Widget::*provice_city_changefunc)(int)=&Widget::provice_city_change;

    connect(ui->province_comboBox,qcomboxsignal,this,provice_city_changefunc);

    //或者用qt4的方式
    //connect(ui->province_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(provice_city_change(int)));

    //输出结果
    //把默认的Cancel改个名字
    ui->check_buttonBox->button(QDialogButtonBox::Cancel)->setText("Clear");

    connect(ui->check_buttonBox,&QDialogButtonBox::accepted,this,&Widget::getres);
    connect(ui->check_buttonBox,&QDialogButtonBox::rejected,this,&Widget::clears);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::addcitys()
{
    citylist.append(QStringList{"成都市","自贡市","攀枝花市","泸州市"});
    citylist.push_back({"西安","咸阳","汉中","渭南","延安"});
    citylist<<QStringList{"杭州市","宁波市","温州市","嘉兴市"};
}

void Widget::getres()
{

    QString name,provice,city;
    name=ui->name_lineEdit->text();
    provice=ui->province_comboBox->currentText();
    city=ui->city_comboBox->currentText();

    ui->lineEdit_2->setText("姓名:"+name+" 省份:"+provice+" 城市:"+city);
}

void Widget::clears()
{
    ui->lineEdit_2->clear();
}

void Widget::provice_city_change(int index)
{
    ui->city_comboBox->clear();

    ui->city_comboBox->addItems(citylist[index]);
}

