#include "widget.h"
#include "ui_widget.h"
#include <QRandomGenerator> //随机数
#include <QStringList>

QStringList iconlist{":/img/1.png"};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置条目相邻交替颜色
    ui->listWidget->setAlternatingRowColors(true);

    //单选按钮加入按钮组
    btngroup = new QButtonGroup(this);
    btngroup->addButton(ui->listmode,0);
    btngroup->addButton(ui->iconmode,1);
    //设置默认是列表模式
    ui->listmode->setChecked(true);
    ui->listWidget->setViewMode(QListView::ListMode);
    //单击条目，显示在line中
    connect(ui->listWidget,&QListWidget::itemClicked,this,&Widget::currentitemClicked);
    //双击条目，编辑
    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&Widget::currentDoubleitemClicked);
    //选择模式切换
    connect(ui->listmode,&QRadioButton::clicked,this,&Widget::oncheck);
    connect(ui->iconmode,&QRadioButton::clicked,this,&Widget::oncheck);
    //添加，插入，删除
    connect(ui->additem,&QPushButton::clicked,this,&Widget::Additem);
    connect(ui->insertitem,&QPushButton::clicked,this,&Widget::Insertitem);
    connect(ui->deleteitem,&QPushButton::clicked,this,&Widget::Deleteitem);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::oncheck(bool checked)
{
    int index=btngroup->checkedId();
    if(index==0){
        ui->listWidget->setViewMode(QListView::ListMode);
    }
    else{
        ui->listWidget->setViewMode(QListView::IconMode);
    }
}

void Widget::currentitemClicked(QListWidgetItem *item)
{
    ui->currentitem->setText(item->text());
}

void Widget::currentDoubleitemClicked(QListWidgetItem *item)
{
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled);
}

void Widget::Additem()
{
    int index=QRandomGenerator::global()->generate()%1; //获取随机数，当前例子中，图标只设置了一个

    QIcon icon(iconlist[index]);
    QString test=ui->lineEdit->text();

    QListWidgetItem *item=new QListWidgetItem(icon,test);
    ui->listWidget->addItem(item);
}

void Widget::Insertitem()
{
    int index=QRandomGenerator::global()->generate()%1; //获取随机数，当前例子中，图标只设置了一个

    QIcon icon(iconlist[index]);
    QString test=ui->lineEdit->text();

    int row=ui->listWidget->currentRow(); //在对应行前面插
    QListWidgetItem *item=new QListWidgetItem(icon,test);
    ui->listWidget->insertItem(row,item);
}

void Widget::Deleteitem()
{
#if 1
    //第一种
    QListWidgetItem *item=ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(item);
    delete item;
#else
    //第二种
    int row=ui->listWidget->currentRow();
    ui->listWidget->takeItem(row);
    delete item;
#endif
}

