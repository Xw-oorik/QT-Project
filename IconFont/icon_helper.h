#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QFont>
#include <QAbstractButton>
#include <QLabel>
#define FONT_WESOME_4 "FontAwesome"
#define FONT_WESOME_4_PATH ":/Font/fontawesome-webfont.ttf"



#define FONT_WETHER "pe-icon-set-weather"
#define FONT_WETHER_PATH ":/Font/pe-icon-set-weather.ttf"

#define FONT_ALBB "FontAlibaba"
#define FONT_ALBB_PATH ":/Font/iconfont.ttf"

class IconHelper: public QObject
{
    Q_OBJECT
private:
    explicit IconHelper(QObject* parent = nullptr);

    static IconHelper * help;
public:
    static IconHelper * getinstance();
    QList<int> getAwesome4Icons();
    QList<int> getWeatherIcons();
    QList<int> getAlibabaIcons();
    //给标签或者按钮设置图标
    void setIcon(QLabel* lbl,QAbstractButton* btn, QString fontFamily, int icon, quint8 size = 10);
    //把图标字体设置成图片
     QPixmap getPixmap(const QColor& color, QString fontFamily, int icon, quint8 size = 10, quint8 width = 12, quint8 height = 12);
private:
    QFont iconFontAwesome4;
    QFont iconFontWeather;
    QFont iconFontAlibaba;
};

#endif // ICONHELPER_H
