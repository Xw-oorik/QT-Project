#include "widget.h"
#include "icon_helper.h"
#include <QRadioButton>
#include <QDebug>
#include <QFontDatabase>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("图标字体"));
    //整体采用垂直布局
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(10);
    vlayout->setContentsMargins(10,10,10,10);

    //顶部窗口
    QWidget *topWidget = new QWidget(this);
    QHBoxLayout *toplayout = new QHBoxLayout(topWidget);
    toplayout->setSpacing(30);
    toplayout->setContentsMargins(5,5,5,5);

    //字体图标库
    radioGroup = new QButtonGroup(this);
    QGroupBox *fontGroup = new QGroupBox(this);
    fontGroup->setTitle("图标字体选择");
    fontGroup->setStyleSheet("font: 18px");
    QVBoxLayout *grouplayout = new QVBoxLayout(fontGroup);
    QStringList radioText{"FontAwesome4", "FontWeather", "FontAlibaba"};
    for(int i = 0 ;i<radioText.size();++i){
        QRadioButton * radio = new QRadioButton(this);
        radio->setText(radioText[i]);
        radio->setMinimumWidth(150);
        radioGroup->addButton(radio,i);
        grouplayout->addWidget(radio);
        //绑定槽函数
        connect(radio,&QRadioButton::clicked,this,&Widget::radioClicked);
    }
    toplayout->addWidget(fontGroup);
    //图标效果
    QGroupBox *showGroup = new QGroupBox(this);
    showGroup->setTitle("效果演示");
    showGroup->setStyleSheet("QGroupBox#showGroup {font: 18px}");
    QHBoxLayout *showlayout = new QHBoxLayout(showGroup);
    showlayout->setSpacing(10);
    for(int i=0;i<8;++i){
        QLabel *lbl = new QLabel(this);
        lbl->setMinimumSize(96,96);
        lbl->setAlignment(Qt::AlignCenter);
        showlayout->addWidget(lbl);
        lblList.push_back(lbl);
        if ( i == 0 ) {
            lbl->setStyleSheet("color: red");
        } else if ( i == 1 ) {
            lbl->setStyleSheet("color: orange");
        } else if ( i == 2 ) {
            //            lbl->setStyleSheet("color: yellow");
            lbl->setStyleSheet("color: #cccc00");
        } else if ( i == 3 ) {
            lbl->setStyleSheet("color: green");
        } else if ( i == 4 ) {
            //            lbl->setStyleSheet("color: cyan");
            lbl->setStyleSheet("color: #00cccc");
        } else if ( i == 5 ) {
            lbl->setStyleSheet("color: blue");
        } else if ( i == 6 ) {
            lbl->setStyleSheet("color: purple");
        }else if ( i == 7 ) {
            lbl->setStyleSheet("color: #ff69b4");
        }
    }
    toplayout->addWidget(showGroup);
    //弹簧
    QSpacerItem *sp = new QSpacerItem(8,20,QSizePolicy::Expanding,QSizePolicy::Fixed);
    toplayout->addItem(sp);
    vlayout->addWidget(topWidget);

    //底部窗口
    QScrollArea *scrollarea = new QScrollArea (this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setMinimumHeight(400);

    QWidget *scrollareacontents = new QWidget(this);
    QVBoxLayout* verticalLayout = new QVBoxLayout(scrollareacontents);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QFrame* frame = new QFrame(scrollareacontents);

    gridLayout = new QGridLayout(frame);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    verticalLayout->addWidget(frame);

    QSpacerItem* sp2 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);
    verticalLayout->addItem(sp2);
    scrollarea->setWidget(scrollareacontents);

    vlayout->addWidget(scrollarea);
    radioGroup->button(0)->click(); //默认开始选择第一个


    IconHelper::getinstance();

    // QFontDatabase database;
    // foreach (QString strFamily, database.families()) {
    //     qDebug() << strFamily;
    //     foreach (QString strStyle, database.styles(strFamily)) {
    //         QString strSizes;
    //         foreach (int points, database.smoothSizes(strFamily, strStyle)) {
    //             strSizes += QString::number(points) + " ";
    //         }
    //         qDebug() << "\t" << strStyle << "\t" << strSizes;
    //     }
    // }

}

Widget::~Widget() {}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Enter){
        QLabel *lbl = qobject_cast<QLabel*>(watched);
        if(lbl){
            int icon = lbl->toolTip().toInt(nullptr,16);
            QString iconFontName;

            int id = radioGroup->checkedId();
            if ( id == 0 ) {
                iconFontName = FONT_WESOME_4;
            } else if ( id == 1 ) {
                iconFontName = FONT_WETHER;
            } else if ( id == 2 ) {
                iconFontName = FONT_ALBB;
            }

            for ( int i = 0; i < 8; i++ ) {
                IconHelper::getinstance()->setIcon(lblList[i], nullptr,iconFontName, icon, 92);
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}

void Widget::radioClicked()
{
    // 1. 先清空原来的标签
    int count = gridLayout->count();
    while ( count-- ) {
        QWidget* widget = gridLayout->takeAt(count)->widget();
        gridLayout->removeWidget(widget);
        widget->setVisible(false);  // 否则底部原来空白的地方被覆盖
        widget->deleteLater();      // 否则看任务管理器，内存一直增长
    }

    // 2. 获取所有图标
    QList<int>icons;
    QString iconFontName;
    int checkedid = radioGroup->checkedId();
    if(checkedid == 0){
        iconFontName = FONT_WESOME_4;
        icons = IconHelper::getinstance()->getAwesome4Icons();
    }else if(checkedid == 1){
        iconFontName = FONT_WETHER;
        icons = IconHelper::getinstance()->getWeatherIcons();
    }else if(checkedid == 2){
        iconFontName = FONT_WETHER;
        icons = IconHelper::getinstance()->getAlibabaIcons();
    }

    // 3. 显示图标（模拟-显示对应的索引）
    int row, column;
    for ( int i = 0; i < icons.size(); i++ ) {
        QLabel* lbl = new QLabel();

        lbl->setText(QChar(icons[i]));
        lbl->setMinimumSize(36, 36);
        lbl->setAlignment(Qt::AlignCenter);
        // 设置悬浮提示
        QString tooltip = "0x" + QString::number(icons[i], 16).toUpper();
        //qDebug() << "Icon value: " << icons[i] << " Tooltip: " << tooltip;
        lbl->setToolTip(tooltip);
        // 设置正常颜色、光标悬浮的颜色
        lbl->setStyleSheet(R"(
            QLabel {color:#000000;border:1px solid #000000;background-color:rgb(255 , 255 , 255);}
            QLabel:hover {color:#ffffff;border:1px solid #000000;background-color:rgb(0 , 0 , 0);}
        )");
        lbl->installEventFilter(this); //注册过滤函数
        IconHelper::getinstance()->setIcon(lbl, nullptr,iconFontName, icons[i], 32);

        // 每行显示 20 个
        row = i / 20;
        column = i % 20;
        gridLayout->addWidget(lbl, row, column);
    }
}
