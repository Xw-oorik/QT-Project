#include "mainwindow.h"

#include <QContextMenuEvent>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QMessageBox>
#include <QNetworkReply>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QJsonParseError>
#include <QLabel>

#include "ui_mainwindow.h"
#include "weather_tool.h"

#define INCREMENT 3 //温度每次升高1度，y的增量
#define POINT_RADIUS 3//曲线的描点大小
#define TEXT_OFFSET_X 12
#define TEXT_OFFSET_Y 12
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //设置窗口属性
    setWindowFlag(Qt::FramelessWindowHint);  // 无边框
    setFixedSize(width(), height());         // 固定窗口大小

    // 右键菜单：退出程序
    mExitMenu = new QMenu(this);
    mExitAct = new QAction();
    mExitAct->setText(tr("退出"));
    mExitAct->setIcon(QIcon(":/res/close.png"));
    mExitMenu->addAction(mExitAct);

    //把控件添加到数组中
    m_weeklist<<ui->lblWeek0<<ui->lblWeek1<<ui->lblWeek2<<ui->lblWeek3<<ui->lblWeek4<<ui->lblWeek5;
    m_datelist<<ui->lblDate0<<ui->lblDate1<<ui->lblDate2<<ui->lblDate3<<ui->lblDate4<<ui->lblDate5;

    m_typelist<<ui->lblType0<<ui->lblType1<<ui->lblType2<<ui->lblType3<<ui->lblType4<<ui->lblType5;
    m_typeiconlist<<ui->lblTypeIcon0<<ui->lblTypeIcon1<<ui->lblTypeIcon2<<ui->lblTypeIcon3<<ui->lblTypeIcon4<<ui->lblTypeIcon5;

    m_aqilist<<ui->lblQuality0<<ui->lblQuality1<<ui->lblQuality2<<ui->lblQuality3<<ui->lblQuality4<<ui->lblQuality5;

    m_fllist<<ui->lblFl0<<ui->lblFl1<<ui->lblFl2<<ui->lblFl3<<ui->lblFl4<<ui->lblFl5;
    m_fxlist<<ui->lblFx0<<ui->lblFx1<<ui->lblFx2<<ui->lblFx3<<ui->lblFx4<<ui->lblFx5;

    //图标添加，天气类型是key，资源是value
    m_pixmap.insert("暴雪",":/res/type/BaoXue.png");
    m_pixmap.insert("暴雨",":/res/type/BaoYu.png");
    m_pixmap.insert("暴雨转大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    m_pixmap.insert("大暴雨",":/res/type/DaBaoYu.png");
    m_pixmap.insert("大暴雨转特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    m_pixmap.insert("特大暴雪",":/res/type/DaDaoBaoXue.png");
    m_pixmap.insert("特大暴雨",":/res/type/DaDaoBaoYu.png");
    m_pixmap.insert("大雪",":/res/type/DaXue.png");
    m_pixmap.insert("大雨",":/res/type/DaYu.png");


    m_pixmap.insert("冬雨",":/res/type/DongYu.png");
    m_pixmap.insert("多云",":/res/type/DuoYun.png");

    m_pixmap.insert("浮尘",":/res/type/FuChen.png");

    m_pixmap.insert("雷阵雨",":/res/type/LeiZhenYu.png");

    m_pixmap.insert("雷阵雨伴有冰雹",":/res/type/LeiZhenYuBanYouBingBao.png");

    m_pixmap.insert("霾",":/res/type/Mai.png");

    m_pixmap.insert("强沙尘暴",":/res/type/QiangShaChenBao.png");

    m_pixmap.insert("晴",":/res/type/Qing.png");
    m_pixmap.insert("沙尘暴",":/res/type/ShaChenBao.png");

    m_pixmap.insert("特大暴雨",":/res/type/TeDaBaoYu.png");
    m_pixmap.insert("无",":/res/type/undefined.png");

    m_pixmap.insert("雾",":/res/type/Wu.png");

    m_pixmap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");

    m_pixmap.insert("小到中雨",":/res/type/XiaoDaoZhongYu.png");
    m_pixmap.insert("小雪",":/res/type/XiaoXue.png");
    m_pixmap.insert("小雨",":/res/type/XiaoXue.png");
    m_pixmap.insert("雪",":/res/type/Xue.png");

    m_pixmap.insert("扬沙",":/res/type/YangSha.png");

    m_pixmap.insert("阴",":/res/type/Yin.png");
    m_pixmap.insert("雨",":/res/type/Yu.png");
    m_pixmap.insert("雨夹雪",":/res/type/YuJiaXue.png");
    m_pixmap.insert("阵雪",":/res/type/ZhenXue.png");
    m_pixmap.insert("阵雨",":/res/type/ZhenYu.png");
    m_pixmap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    m_pixmap.insert("中到大雨",":/res/type/ZhongDaoDaYu.png");
    m_pixmap.insert("中雪",":/res/type/ZhongXue.png");
    m_pixmap.insert("中雨",":/res/type/ZhongYu.png");


    connect(mExitAct, &QAction::triggered, this, [=]() { qApp->exit(0); });

    m_manger = new QNetworkAccessManager(this);
    connect(m_manger,&QNetworkAccessManager::finished,this,&MainWindow::onReply);


    //给一个默认的
    sendrequest("101010100");
    //搜索城市天气
    connect(ui->btnSearch,&QPushButton::clicked,this,&MainWindow::Serachcity);

    //绘图曲线，注册过滤器
    ui->lblHighCurve->installEventFilter(this);
    ui->lblLowCurve->installEventFilter(this);

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    mExitMenu->exec(QCursor::pos());
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_offset = event->globalPos()-this->mapToGlobal(QPoint(0,0));
    //m_offset = event->globalPos()-this->pos();  //same as
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-m_offset);
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint)
    {
        if(watched==ui->lblHighCurve)
        {
            qDebug()<<u8"绘制高温曲线";
            drawhigh();
        }
        else if(watched==ui->lblLowCurve)
        {
            qDebug()<<u8"绘制低温曲线";
            drawlow();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::sendrequest(const QString &code)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://t.weather.itboy.net/api/weather/city/"+code));
    m_manger->get(request);
}

void MainWindow::parseJson( QByteArray &array)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(err.error!=QJsonParseError::NoError){
        return ;
    }
    QJsonObject rootobj = doc.object();

    qDebug()<<rootobj.value("message").toString();

    //当天
    QJsonObject dataobj = rootobj.value("data").toObject();

    m_today.data = rootobj.value("date").toString();

    m_today.city = rootobj.value("cityInfo").toObject().value("city").toString();


    m_today.shidu = dataobj.value("shidu").toString();
    m_today.testdata = dataobj.value("ganmao").toString();
    m_today.wendu = dataobj.value("wendu").toString().toInt();
    m_today.pm25 = dataobj.value("pm25").toDouble();
    m_today.quality = dataobj.value("quality").toString();


    //昨天
    QJsonObject yesterdayobj = dataobj.value("yesterday").toObject();

    m_week[0].data = yesterdayobj.value("ymd").toString();

    m_week[0].week = yesterdayobj.value("week").toString();
    m_week[0].type = yesterdayobj.value("type").toString();
    m_week[0].fx = yesterdayobj.value("fx").toString();
    m_week[0].fl = yesterdayobj.value("fl").toString();

    QString s;
    s = yesterdayobj.value("high").toString().split(" ").at(1);
    s=s.left(s.length()-1);
    m_week[0].high =s.toInt();

    s= yesterdayobj.value("low").toString().split(" ").at(1);
    s= s.left(s.length()-1);
    m_week[0].low =s.toInt();

    m_week[0].fx = yesterdayobj.value("fx").toString();
    m_week[0].fl = yesterdayobj.value("fl").toString();
    m_week[0].aqi = yesterdayobj.value("aqi").toDouble();


    //5天
    QJsonArray forecastarray = dataobj.value("forecast").toArray();
    for(int i=0;i<5;++i)
    {
        QJsonObject forecastobj = forecastarray[i].toObject();
        m_week[i+1].data = forecastobj.value("ymd").toString();
        m_week[i+1].week = forecastobj.value("week").toString();
        m_week[i+1].type = forecastobj.value("type").toString();
        m_week[i+1].fx = forecastobj.value("fx").toString();
        m_week[i+1].fl = forecastobj.value("fl").toString();
        m_week[i+1].aqi = forecastobj.value("aqi").toDouble();
        QString highwendu = forecastobj.value("high").toString().split(" ").at(1);
        m_week[i+1].high = highwendu.left(highwendu.size()-1).toInt();

        QString lowwendu = forecastobj.value("low").toString().split(" ").at(1);
        m_week[i+1].low = lowwendu.left(lowwendu.size()-1).toInt();

    }
    m_week[0].week="昨天";
    m_week[1].week="今天";
    m_week[2].week="明天";

    //今天的补充
    m_today.type = m_week[1].type;
    m_today.fx = m_week[1].fx;
    m_today.fl = m_week[1].fl;
    m_today.high = m_week[1].high;
    m_today.low = m_week[1].low;

    qDebug()<<"this:"<<this->height()<<" "<<this->width();
    qDebug()<<"lblhigh:"<<ui->lblHighCurve->height()<<" "<<ui->lblHighCurve->width();
    //更新ui
    updateUI();
    //画曲线
    updateT();
}

void MainWindow::updateUI()
{
    //右上角
    ui->lblDate->setText(QDateTime::fromString(m_today.data,"yyyyMMdd").toString("yyyy/MM/dd")+" "+m_today.city);

    //左边
    ui->lblCity->setText(m_today.city);
    ui->lblType->setText(m_today.type);
    ui->lblLowHigh->setText(QString::number(m_today.low)+"°C"+"~"+QString::number(m_today.high)+"°C");
    ui->lblGanMao->setText("感冒指数:"+m_today.testdata);
    ui->lblTemp->setText(QString::number(m_today.wendu));
    ui->lblWindFx->setText(m_today.fx);
    ui->lblWindFl->setText(m_today.fl);
    ui->lblShiDu->setText(m_today.shidu);
    ui->lblQuality->setText(m_today.quality);
    ui->lblTypeIcon->setPixmap(QPixmap(m_pixmap[m_today.type]));

    //右边
    for(int i=0;i<6;++i)
    {
        //日期和星期几

        m_weeklist[i]->setText("周"+m_week[i].week.right(1));
        m_weeklist[0]->setText(m_week[0].week);
        m_weeklist[1]->setText(m_week[1].week);
        m_weeklist[2]->setText(m_week[2].week);

        QStringList qs = m_week[i].data.split("-");
        m_datelist[i]->setText(qs[1]+"/"+qs[2]);

        m_typeiconlist[i]->setPixmap(QPixmap(m_pixmap[m_week[i].type]));
        m_typelist[i]->setText(m_week[i].type);

        //更新空气质量
        if(m_week[i].aqi>=0&&m_week[i].aqi<=50){
            m_aqilist[i]->setText("优");
            m_aqilist[i]->setStyleSheet("background-color:rgb(121,184,0)");
        }
        else if(m_week[i].aqi>50&&m_week[i].aqi<=100){
            m_aqilist[i]->setText("良");
            m_aqilist[i]->setStyleSheet("background-color:rgb(255,187,23)");
        }
        else if(m_week[i].aqi>100&&m_week[i].aqi<=150){
            m_aqilist[i]->setText("轻度");
            m_aqilist[i]->setStyleSheet("background-color:rgb(255,87,97)");
        }
        else if(m_week[i].aqi>150&&m_week[i].aqi<=200){
            m_aqilist[i]->setText("中度");
            m_aqilist[i]->setStyleSheet("background-color:rgb(235,17,27)");
        }
        else if(m_week[i].aqi>200&&m_week[i].aqi<=250){
            m_aqilist[i]->setText("重度");
            m_aqilist[i]->setStyleSheet("background-color:rgb(171,1,2)");
        }
        else{
            m_aqilist[i]->setText("严重");
            m_aqilist[i]->setStyleSheet("background-color:rgb(110,10,0)");
        }
        //风向风级
        m_fllist[i]->setText(m_week[i].fl);
        m_fxlist[i]->setText(m_week[i].fx);
    }
}

void MainWindow::drawhigh()
{
    QPainter painter(ui->lblHighCurve);
    painter.setRenderHint(QPainter::Antialiasing,true);

    //获取x坐标
    int pointx[6]{0};
    for(int i=0;i<6;++i)
    {
        pointx[i]=m_weeklist[i]->pos().x()+m_weeklist[i]->width()/2;
    }

    //获取y坐标
    int tempwendu=0;
    int tempwenduarg=0; //最高温平均值
    for(int i=0;i<6;++i)
    {
        tempwendu+=m_week[i].high;
    }
    tempwenduarg=tempwendu/6;
    int pointy[6]{0};
    int tcenter =ui->lblHighCurve->height()/2; //高温曲线那个标签的中心长度是多少
    for(int i=0;i<6;++i)
    {
        pointy[i]=tcenter-(m_week[i].high-tempwenduarg)*INCREMENT;
    }

    //开始绘制
    QPen pen=painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(255,175,12));
    painter.setPen(pen);
    painter.setBrush(QColor(255,120,128));
    //画点，写文本
    for(int i=0;i<6;++i)
    {
        painter.drawEllipse(pointx[i],pointy[i],POINT_RADIUS,POINT_RADIUS);
        painter.drawText(pointx[i]-TEXT_OFFSET_X,pointy[i]-TEXT_OFFSET_Y,QString::number(m_week[i].high)+"°");
    }
    //画线
    for(int i=0;i<5;++i)
    {
        pen.setStyle(Qt::SolidLine);
        painter.drawLine(pointx[i],pointy[i],pointx[i+1],pointy[i+1]);
    }
}

void MainWindow::drawlow()
{
    QPainter painter(ui->lblLowCurve);
    painter.setRenderHint(QPainter::Antialiasing,true);

    //获取x坐标
    int pointx[6]{0};
    for(int i=0;i<6;++i)
    {
        pointx[i]=m_weeklist[i]->pos().x()+m_weeklist[i]->width()/2;
    }

    //获取y坐标
    int tempwendu=0;
    int tempwenduarg=0; //最高温平均值
    for(int i=0;i<6;++i)
    {
        tempwendu+=m_week[i].low;
    }
    tempwenduarg=tempwendu/6;
    int pointy[6]{0};
    int tcenter =ui->lblLowCurve->height()/2; //高温曲线那个标签的中心长度是多少
    for(int i=0;i<6;++i)
    {
        pointy[i]=tcenter-(m_week[i].low-tempwenduarg)*INCREMENT;
    }

    //开始绘制
    QPen pen=painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor (137, 207, 240));
    painter.setPen(pen);
    painter.setBrush(QColor (137, 207, 240));
    //画点，写文本
    for(int i=0;i<6;++i)
    {
        painter.drawEllipse(pointx[i],pointy[i],POINT_RADIUS,POINT_RADIUS);
        painter.drawText(pointx[i]-TEXT_OFFSET_X,pointy[i]-TEXT_OFFSET_Y,QString::number(m_week[i].low)+"°");
    }
    //画线
    for(int i=0;i<5;++i)
    {
        pen.setStyle(Qt::DotLine);
        painter.drawLine(pointx[i],pointy[i],pointx[i+1],pointy[i+1]);
    }

}

void MainWindow::updateT()
{
   ui->lblHighCurve->update();//重绘制曲线，在更新城市之后，重绘制
   ui->lblLowCurve->update();
}

void MainWindow::onReply(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error()!= QNetworkReply::NoError ||status_code!=200) {
            qDebug("%s(%d) error:%s",__FUNCTION__,__LINE__,reply->errorString().toLatin1().data());
            QMessageBox::warning(this,"天气","请求数据错误",QMessageBox::Ok|QMessageBox::Cancel);
    }
    else {
        qDebug()<<"operation:"<<reply->operation();
        qDebug()<<"status code:"<<status_code;
        qDebug()<<"url:"<<reply->url();
        qDebug()<<"raw header:"<<reply->rawHeaderList();

        QByteArray array = reply->readAll();

        qDebug()<<"read all:"<<array.data();
        parseJson(array);
    }
    reply->deleteLater();//很重要

}
//跟搜索框绑定一起
void MainWindow::Serachcity()
{
    QString cityname=ui->leCity->text();
    QString citycode = Weather_Tool::SetCityCode(cityname);
    if(citycode.isEmpty()){
        QMessageBox::warning(this,"城市天气","城市输入有误，请重新输入",QMessageBox::Yes|QMessageBox::No);
        return;
    }
    sendrequest(citycode); //调发送请求
}
