#include "widget.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QRandomGenerator64>>
QString Widget::codeFilePath;
QString Widget::jsonFilePath;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(10,10,10,10);
    gridLayout->setSpacing(10);

    this->setWindowTitle("语法高亮");

    //代码高亮
    QVBoxLayout * codeLayout = new QVBoxLayout(this);
    codeLayout->setContentsMargins(0,0,0,0);
    codeLayout->setSpacing(5);

    QHBoxLayout * codetitleLayout = new QHBoxLayout(this);
    codetitleLayout->setContentsMargins(0,0,0,0);
    codetitleLayout->setSpacing(0);

    //复选框
    chkCode = new QCheckBox(this);
    chkCode->setText("代码高亮");
    codetitleLayout->addWidget(chkCode);
    //弹簧
    QSpacerItem *sp = new QSpacerItem(20,8,QSizePolicy::Expanding,QSizePolicy::Fixed);
    codetitleLayout->addSpacerItem(sp);
    //打开文件
    btnCodeBrowse = new QRadioButton(this);
    btnCodeBrowse->setText("打开文件");
    codetitleLayout->addWidget(btnCodeBrowse);

    QSpacerItem* sp2 = new QSpacerItem(64, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    codetitleLayout->addSpacerItem(sp2);

    radioKeyboard = new QRadioButton(this);
    radioKeyboard->setText("模拟键盘输入");
    codetitleLayout->addWidget(radioKeyboard);

    codeRadioGroup = new QButtonGroup(this);
    codeRadioGroup->addButton(btnCodeBrowse,0);
    codeRadioGroup->addButton(radioKeyboard,1);

    codeLayout->addLayout(codetitleLayout);
    codeEditor = new QTextEdit(this);
    codeLayout->addWidget(codeEditor);

    gridLayout->addLayout(codeLayout,0,0);
    codetimer = new QTimer(this);

    // JSON高亮
    QVBoxLayout* jsonLayout = new QVBoxLayout(this);
    jsonLayout->setContentsMargins(0, 0, 0, 0);
    jsonLayout->setSpacing(5);

    //  标题
    QHBoxLayout* jsonTitleLayout = new QHBoxLayout(this);
    jsonTitleLayout->setContentsMargins(0, 0, 0, 0);
    jsonTitleLayout->setSpacing(0);

    // 复选框
    jsonCode = new QCheckBox(this);
    jsonCode->setText("JSON高亮");
    jsonTitleLayout->addWidget(jsonCode);

    // 弹簧
    QSpacerItem* sp4 = new QSpacerItem(20, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    jsonTitleLayout->addSpacerItem(sp4);

    // 打开文件按钮
    btnJsonBrowse = new QRadioButton(this);
    btnJsonBrowse->setText("打开文件");
    jsonTitleLayout->addWidget(btnJsonBrowse);

    // 弹簧
    QSpacerItem* sp5 = new QSpacerItem(64, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    jsonTitleLayout->addSpacerItem(sp5);

    radioJsonKeyboard = new QRadioButton(this);
    radioJsonKeyboard->setText("模拟键盘输入");
    jsonTitleLayout->addWidget(radioJsonKeyboard);

    jsonRadioGroup = new QButtonGroup(this);
    jsonRadioGroup->addButton(btnJsonBrowse,0);
    jsonRadioGroup->addButton(radioJsonKeyboard, 1);

    jsonLayout->addLayout(jsonTitleLayout);

    jsonEditor = new QTextEdit;
    jsonLayout->addWidget(jsonEditor);

    gridLayout->addLayout(jsonLayout, 1, 0);
    jsontimer = new QTimer(this);

    //下机位
    QVBoxLayout* deviceLayout = new QVBoxLayout(this);
    deviceLayout->setContentsMargins(0, 0, 0, 0);
    deviceLayout->setSpacing(5);
    QHBoxLayout* deviceTitleLayout = new QHBoxLayout(this);
    deviceTitleLayout->setContentsMargins(0, 0, 0, 0);
    deviceTitleLayout->setSpacing(0);
    devicechkbox = new QCheckBox(this);
    devicechkbox->setText("下位机温湿度高亮");
    deviceTitleLayout->addWidget(devicechkbox);
    QSpacerItem* sp6 = new QSpacerItem(20, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    deviceTitleLayout->addSpacerItem(sp6);
    startaccept = new QPushButton(this);
    startaccept->setText("启动接收");
    cleardata = new QPushButton(this);
    QSpacerItem* sp7 = new QSpacerItem(64, 8, QSizePolicy::Expanding, QSizePolicy::Fixed);
    deviceTitleLayout->addSpacerItem(sp7);
    cleardata->setText("清空数据");
    deviceTitleLayout->addWidget(startaccept);
    deviceTitleLayout->addWidget(cleardata);

    deviceLayout->addLayout(deviceTitleLayout);
    deviceEditor = new QTextEdit;
    deviceEditor->document()->setMaximumBlockCount(100);  // 最多显示100行
    deviceEditor->setReadOnly(true);                      // 不允许编辑
    deviceEditor->setStyleSheet("font: 12px Courier");
    deviceLayout->addWidget(deviceEditor);
    deviceTimer = new QTimer(this);
    // 子布局 deviceLayout 的左上角位于网格的第 0 行、第 1 列
    // 子布局 deviceLayout 跨越 2 行
    // 子布局 deviceLayout 跨越 1 列
    gridLayout->addLayout(deviceLayout, 0, 1, 2, 1);

    connection();

}

Widget::~Widget() {}

void Widget::loadFile(QTextEdit *textEdit, const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    file.close();
    textEdit->setPlainText(QString(array));
}

void Widget::connection()
{

    connect(btnCodeBrowse,&QRadioButton::clicked,this,[=]{
        QString filename = QFileDialog::getOpenFileName(this,"打开文件",QDir::currentPath(),"CODE(*.cpp *.cc *.h *.c *.hpp)");
        if(filename!=nullptr){
            codeFilePath = filename;
            loadFile(codeEditor,filename);
            codetimer->stop();
            jsonEditor->setReadOnly(false);
        }
    });


    connect(btnJsonBrowse,&QRadioButton::clicked,this,[=]{
        QString filename = QFileDialog::getOpenFileName(this,"打开文件",QDir::currentPath(),"JSON(*.json *.txt)");
        if(filename!=nullptr){
            jsonFilePath = filename;
            loadFile(jsonEditor,filename);
            jsontimer->stop();
            jsonEditor->setReadOnly(false);
        }
    });

    connect(radioKeyboard,&QRadioButton::clicked,this,[=]{
        if(codeFilePath.size()){
            codeEditor->clear();
            QFile* file = new QFile(codeFilePath);
            // QFile默认支持的格式是utf-8格式
            file->open(QIODevice::ReadOnly);

            QByteArray array = file->readAll();
            file->close();
            codeString = QString(array);
            codeCharIndex = 0;
            codetimer->start(20);
            jsonEditor->setReadOnly(true);
        }else{
            QMessageBox::warning(this, "警告", "之前未打开过文件(.cpp .cc ..)");
        }
    });
    connect(radioJsonKeyboard,&QRadioButton::clicked,this,[=]{
        if(jsonFilePath.size()){
            jsonEditor->clear();
            QFile* file = new QFile(jsonFilePath);
            file->open(QIODevice::ReadOnly);
            QByteArray array = file->readAll();
            file->close();
            jsonString = QString(array);
            jsonCharIndex = 0;
            jsontimer->start(20);
            jsonEditor->setReadOnly(true);
        }else{
            QMessageBox::warning(this, "警告", "之前未打开过文件(.json .txt ..)");
        }
    });
    connect(codetimer, &QTimer::timeout, this, &Widget::codetimeout);
    connect(jsontimer,&QTimer::timeout,this,&Widget::jsontimeout);
    connect(deviceTimer,&QTimer::timeout,this,&Widget::onDeviceTimeout);
    connect(chkCode,&QCheckBox::stateChanged,this,[=]{
        if(chkCode->isChecked()){
            codeHighlight = new CodeHighlighter(codeEditor->document());
        }else{
            delete codeHighlight;
        }
    });
    connect(jsonCode,&QCheckBox::stateChanged,this,[=]{
        if(jsonCode->isChecked()){
            jsonHighlighter = new JsonHighlighter(jsonEditor->document());
        }else{
            delete jsonHighlighter;
        }
    });
    connect(devicechkbox,&QCheckBox::stateChanged,this,[=]{
        if(devicechkbox->isChecked()){
            deviceHighlighter = new DeviceHighlighter(deviceEditor->document());
        }else{
            delete deviceHighlighter;
        }
    });
    connect(startaccept,&QPushButton::clicked,this,[=]{
        if(deviceTimer->isActive()){
            deviceTimer->stop();
            startaccept->setText("开始接收");
        }else{
            deviceTimer->start(500);
            startaccept->setText("停止接收");
        }
    });
    connect(cleardata,&QPushButton::clicked,this,[=]{
        deviceEditor->clear();
    });

}

void Widget::codetimeout()
{
    if(codeCharIndex<codeString.count()){
        QString ch = codeString.at(codeCharIndex++);

        codeEditor->insertPlainText(ch);
        codeEditor->moveCursor(QTextCursor::End);  // 移动光标到最后一行

    }else{
        codeCharIndex = 0;
        codeEditor->clear();
    }
}

void Widget::jsontimeout()
{
    if(jsonCharIndex<jsonString.count()){
        QString ch = jsonString.at(jsonCharIndex++);

        jsonEditor->insertPlainText(ch);
        jsonEditor->moveCursor(QTextCursor::End);  // 移动光标到最后一行

    }else{
        jsonCharIndex = 0;
        jsonEditor->clear();
    }
}

void Widget::onDeviceTimeout()
{
    QDateTime datatime = QDateTime::currentDateTime();

    int temp = -10 + QRandomGenerator64::global()->generate()%50;
    QString strtemp;
    if(temp<=-8){
        strtemp = QString("%1%2%3").arg("Temperature:").arg(temp,3,10).arg("°C (↓Lower)");
    }else if ( temp >= 38 ) {
        strtemp = QString("%1%2%3").arg("Temperature:").arg(temp, 3, 10).arg("°C (↑Upper)");
    } else {
        strtemp = QString("%1%2%3").arg("Temperature:").arg(temp, 3, 10).arg("°C (-Normal)");
    }
    int humi = 10 + QRandomGenerator64::global()->generate() % 80;  // [10, 90]
    QString strHumi;
    if ( humi <= 15 ) {
        strHumi = QString("%1%2%3").arg("Humidity:").arg(humi, 3, 10).arg("% (↓Lower)");
    } else if ( humi >= 85 ) {
        strHumi = QString("%1%2%3").arg("Humidity:").arg(humi, 3, 10).arg("% (↑Upper)");
    } else {
        strHumi = QString("%1%2%3").arg("Humidity:").arg(humi, 3, 10).arg("% (-Normal)");
    }
    deviceEditor->append(datatime.toString("[yyyy-MM-dd hh:mm:ss] ") + strtemp + "  " + strHumi);
}
