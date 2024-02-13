#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置行表头,自适应
    QStringList tablelist;
    tablelist<<"姓名";
    tablelist<<"年龄";
    tablelist<<"性别";
    tablelist<<"籍贯";
    int num=tablelist.size();
    ui->tableWidget->setColumnCount(num);
    ui->tableWidget->setHorizontalHeaderLabels(tablelist);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //列表头居中设置
    QHeaderView *headerView = ui->tableWidget->verticalHeader();
    headerView->setDefaultAlignment(Qt::AlignHCenter| Qt::AlignVCenter);

    //初始化数据
    appendOneRow("王x",20,"男","陕西");
    appendOneRow("小7",15,"女","香港");

    //外观设置部分
    appsettings();

    //选择模式
    choosesettings();

    //选择单元格显示到文本框
    connect(ui->tableWidget,&QTableWidget::itemClicked,this,&Widget::showtest);

    //数据操作
    datamanipulation();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::appendOneRow(QString name, int age, QString sex, QString province)
{
    //获取当前的总行数，设置总行数加一，相当于新添加一 行
    int count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(count+1);
    QList<QTableWidgetItem*> qls;
    QTableWidgetItem* nameitem=new QTableWidgetItem(name);
    QTableWidgetItem* ageitem=new QTableWidgetItem(QString::number(age));
    QTableWidgetItem* sexitem=new QTableWidgetItem(sex);
    QTableWidgetItem* provinceitem=new QTableWidgetItem(province);

    qls<<nameitem<<ageitem<<sexitem<<provinceitem;
    int i=0;
    for(auto& item:qls){
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(count,i,item);
        i+=1;
    }
    return ;

}

void Widget::appsettings()
{
    //行表头
    if(ui->tableWidget->horizontalHeader()){
        ui->rowcheck->setChecked(true);
    }
    else{
        ui->rowcheck->setChecked(false);
    }
    connect(ui->rowcheck,&QCheckBox::stateChanged,this,[&](int state){
        if(state==Qt::Checked){
            ui->tableWidget->horizontalHeader()->show();
        }
        else{
            ui->tableWidget->horizontalHeader()->hide();
        }
    });
    //列表头
    if(ui->tableWidget->verticalHeader()->isHidden()){
        ui->colcheck->setChecked(false);
    }
    else{
        ui->colcheck->setChecked(true);
    }
    connect(ui->colcheck,&QCheckBox::stateChanged,this,[&](int state){
        if(state==Qt::Checked){
            ui->tableWidget->verticalHeader()->show();
        }
        else{
            ui->tableWidget->verticalHeader()->hide();
        }
    });
    //交替背景色
    if(ui->tableWidget->alternatingRowColors()){
        ui->backcheck->setChecked(true);
    }
    else{
        ui->backcheck->setChecked(false);
    }
    connect(ui->backcheck,&QCheckBox::stateChanged,this,[&](int state){
        if(state==Qt::Checked){
            ui->tableWidget->setAlternatingRowColors(true);
        }
        else{
            ui->tableWidget->setAlternatingRowColors(false);
        }
    });
    //单元格可编辑
    if(ui->tableWidget->editTriggers()==QAbstractItemView::NoEditTriggers)
    {
        ui->itemeditcheck->setChecked(false);
    }
    else{
        ui->itemeditcheck->setChecked(true);
    }
    connect(ui->itemeditcheck,&QCheckBox::stateChanged,this,[=](int state){
        if(state==Qt::Checked){
            ui->tableWidget->setEditTriggers(QAbstractItemView::EditKeyPressed
                                             |QAbstractItemView::DoubleClicked
                                             |QAbstractItemView::SelectedClicked);
        }
        else{
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    });
    //设置样式表
    connect(ui->qsspushButton,&QPushButton::clicked,this,[&](){
        QString cellStyle =
                R"(
                QTableView
                {
                text-align:center;
                background-color: rgba(255, 255, 255, 0);
                alternate-background-color:#e3edf9;
                font:14px "微软雅黑";
                color:#677483;
                gridline-color: #ccddf0;
                }
                )";

        const QString horizontalHeaderStyle =
                R"(
                QHeaderView::section {
                color: black;
                font:bold 14px "微软雅黑";
                text-align:center;
                height:32px;
                background-color: #d1dff0;
                border:1px solid #8faac9;
                border-left:none;
                }
                )";

        const QString verticalHeaderStyle =
                R"(
                QHeaderView::section {
                color: black;
                font:bold 14px "微软雅黑";
                width:60px;
                text-align:center;

                background-color: #d1dff0;
                border:1px solid #8faac9;
                border-left:none;
                }
                )";

        ui->tableWidget->setStyleSheet(cellStyle);
        ui->tableWidget->horizontalHeader()->setStyleSheet(horizontalHeaderStyle);
        ui->tableWidget->verticalHeader()->setStyleSheet(verticalHeaderStyle);
    });

}

void Widget::choosesettings()
{
    mbtg = new QButtonGroup(this);
    mbtg->addButton(ui->itemradiobutton, 0);
    mbtg->addButton(ui->rowradiobutton, 1);
    connect(ui->itemradiobutton,&QRadioButton::clicked,this,&Widget::choseradio);
    connect(ui->rowradiobutton,&QRadioButton::clicked,this,&Widget::choseradio);

}

void Widget::datamanipulation()
{

    //添加一行
    connect(ui->add1,&QPushButton::clicked,this,[&](){
        QString name=ui->n2->text();
        QString age=ui->a2->text();
        QString sex=ui->s2->text();
        QString pro=ui->p2->text();
        appendOneRow(name,age.toInt(),sex,pro);
    });

    //插入一行
    connect(ui->append1,&QPushButton::clicked,this,[&](){
        QString name=ui->n2->text();
        QString age=ui->a2->text();
        QString sex=ui->s2->text();
        QString pro=ui->p2->text();
        //获取当前行数，设置行数加一，相当于新添加一 行
        int count = ui->tableWidget->currentRow();
        ui->tableWidget->insertRow(count);
        QList<QTableWidgetItem*> qls;
        QTableWidgetItem* nameitem=new QTableWidgetItem(name);
        QTableWidgetItem* ageitem=new QTableWidgetItem(age);
        QTableWidgetItem* sexitem=new QTableWidgetItem(sex);
        QTableWidgetItem* provinceitem=new QTableWidgetItem(pro);

        qls<<nameitem<<ageitem<<sexitem<<provinceitem;
        int i=0;
        for(auto& item:qls){
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(count,i,item);
            i+=1;
        }
    });
    //删除当前行
    connect(ui->destroy1,&QPushButton::clicked,this,[&](){
        //获取当前行数，设置行数加一，相当于新添加一 行
        int count = ui->tableWidget->currentRow();
        ui->tableWidget->removeRow(count);
    });
    //修改当前行
    connect(ui->change1,&QPushButton::clicked,this,[&](){
        QString name=ui->n2->text();
        QString age=ui->a2->text();
        QString sex=ui->s2->text();
        QString pro=ui->p2->text();
        int count = ui->tableWidget->currentRow();

        QTableWidgetItem* nameitem=new QTableWidgetItem(name);
        QTableWidgetItem* ageitem=new QTableWidgetItem(age);
        QTableWidgetItem* sexitem=new QTableWidgetItem(sex);
        QTableWidgetItem* provinceitem=new QTableWidgetItem(pro);

        nameitem->setTextAlignment(Qt::AlignCenter);
        sexitem->setTextAlignment(Qt::AlignCenter);
        ageitem->setTextAlignment(Qt::AlignCenter);
        provinceitem->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(count, 0,     nameitem);
        ui->tableWidget->setItem(count, 1,   ageitem);
        ui->tableWidget->setItem(count, 2,      sexitem);
        ui->tableWidget->setItem(count, 3, provinceitem);
    });
}

void Widget::showtest(QTableWidgetItem *item)
{
    int row=item->row();

    ui->n2->setText(ui->tableWidget->item(row,0)->text());
    ui->a2->setText(ui->tableWidget->item(row,1)->text());
    ui->s2->setText(ui->tableWidget->item(row,2)->text());
    ui->p2->setText(ui->tableWidget->item(row,3)->text());
}

void Widget::choseradio()
{
    int click=mbtg->checkedId();
    if(click==0){
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    }
    else if(click==1){
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}

