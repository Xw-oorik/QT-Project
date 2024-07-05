#include "icon_helper.h"
#include <QFontDatabase>
#include <QDebug>
#include <QPainter>
IconHelper * IconHelper::help = nullptr;



IconHelper::IconHelper(QObject *parent)
{
    QFontDatabase fontDb;
    int fontId;

    if(!fontDb.families().contains(FONT_WESOME_4)){
        fontId = fontDb.addApplicationFont(FONT_WESOME_4_PATH);
        QStringList fontFamilies = fontDb.applicationFontFamilies(fontId);
        qDebug()<<fontFamilies;
        if(fontFamilies.count()){
            iconFontAwesome4 = QFont(FONT_WESOME_4);
            iconFontAwesome4.setHintingPreference(QFont::PreferNoHinting);
        }
    }


    if ( !fontDb.families().contains(FONT_WETHER) ) {
        fontId = fontDb.addApplicationFont(FONT_WETHER_PATH);
        QStringList fontFamilies = fontDb.applicationFontFamilies(fontId);
        qDebug()<<fontFamilies;
        if ( fontFamilies.count() > 0 ) {
            iconFontWeather = QFont(FONT_WETHER);
            iconFontWeather.setHintingPreference(QFont::PreferNoHinting);
        }
    }

    // 添加 FontAlibaba
    if ( !fontDb.families().contains(FONT_ALBB) ) {
        fontId = fontDb.addApplicationFont(FONT_ALBB_PATH);
        QStringList fontFamilies = fontDb.applicationFontFamilies(fontId);
        qDebug()<<fontFamilies;
        if ( fontFamilies.count() > 0 ) {
            iconFontAlibaba = QFont(FONT_ALBB);
            iconFontAlibaba.setHintingPreference(QFont::PreferNoHinting);
        }
    }
}

IconHelper *IconHelper::getinstance()
{
    if(!help){
        QMutex mutex;
        QMutexLocker locker(&mutex);
        if(!help){
            help = new IconHelper();}
    }
    return help;
}

QList<int> IconHelper::getAwesome4Icons()
{
    int start = 0xf000;
    int end = 0xf2e0;

    // 0xf000~0xf2e0 范围内，有些是空的
    QList<int> emptyList = {0xf00f, 0xf01f, 0xf020, 0xf03f, 0xf04f, 0xf05f, 0xf06f, 0xf07f, 0xf08f, 0xf09f, 0xf0af, 0xf0b3, 0xf0b4, 0xf0b5, 0xf0b6, 0xf0b7,
                            0xf0b8, 0xf0b9, 0xf0ba, 0xf0bb, 0xf0bc, 0xf0bd, 0xf0be, 0xf0bf, 0xf0bf, 0xf0cf, 0xf0df, 0xf0ef, 0xf0ff, 0xf10f, 0xf116, 0xf117,
                            0xf11f, 0xf12f, 0xf13f, 0xf14f, 0xf15f, 0xf16f, 0xf17f, 0xf18f, 0xf19f, 0xf1af, 0xf1bf, 0xf1cf, 0xf1df, 0xf1ef, 0xf1ff, 0xf20f,
                            0xf21f, 0xf220, 0xf22e, 0xf22f, 0xf23f, 0xf24f, 0xf25f, 0xf26f, 0xf27f, 0xf28f, 0xf29f, 0xf2af, 0xf2bf, 0xf2cf, 0xf2df};

    QList<int> list;
    for ( int icon = start; icon <= end; icon++ ) {
        // 0xf000~0xf2e0 范围内，有些是空的
        if ( emptyList.contains(icon) ) {
            continue;
        }
        list.append(icon);
    }

    return list;
}

QList<int> IconHelper::getWeatherIcons()
{
    QList<int> list;

    for ( int i = 0xe900; i <= 0xe9cf; i++ ) {
        list.append(i);
    }

    return list;
}

QList<int> IconHelper::getAlibabaIcons()
{
    QList<int> list;

    // 图表
    for ( int i = 0xa000; i <= 0xa027; i++ ) {
        list.append(i);
    }

    // 仪表盘
    for ( int i = 0xa100; i <= 0xa106; i++ ) {
        list.append(i);
    }

    // 表格
    for ( int i = 0xa200; i <= 0xa20e; i++ ) {
        list.append(i);
    }

    // 日历
    for ( int i = 0xa300; i <= 0xa30b; i++ ) {
        list.append(i);
    }

    //  树状图
    for ( int i = 0xa400; i <= 0xa402; i++ ) {
        list.append(i);
    }

    // 标签页
    for ( int i = 0xa500; i <= 0xa505; i++ ) {
        list.append(i);
    }

    // 最大化最小化
    for ( int i = 0xa600; i <= 0xa603; i++ ) {
        list.append(i);
    }

    // 文本编辑器
    for ( int i = 0xa700; i <= 0xa70a; i++ ) {
        list.append(i);
    }

    // 加号
    for ( int i = 0xa900; i <= 0xa901; i++ ) {
        list.append(i);
    }

    // 天气
    for ( int i = 0xaa00; i <= 0xaa0e; i++ ) {
        list.append(i);
    }

    // 换肤
    for ( int i = 0xab00; i <= 0xab03; i++ ) {
        list.append(i);
    }

    return list;
}

void IconHelper::setIcon(QLabel *lbl, QAbstractButton *btn, QString fontFamily, int icon, quint8 size)
{
    if(fontFamily == FONT_WESOME_4){
        iconFontAwesome4.setPixelSize(size);
        if(lbl&&!btn){
            lbl->setFont(iconFontAwesome4);
            lbl->setText((QChar)icon);
        }
        else if(btn&&!lbl){
            btn->setFont(iconFontAwesome4);
            btn->setText((QChar)icon);
        }
    }
    else if(fontFamily == FONT_WETHER){
        iconFontWeather.setPixelSize(size);
        if(lbl&&!btn){
            lbl->setFont(iconFontWeather);
            lbl->setText((QChar)icon);
        }
        else if(btn&&!lbl){
            btn->setFont(iconFontWeather);
            btn->setText((QChar)icon);
        }
    }
    else if(fontFamily == FONT_ALBB){
        iconFontAlibaba.setPixelSize(size);
        if(lbl&&!btn){
            lbl->setFont(iconFontAlibaba);
            lbl->setText((QChar)icon);
        }
        else if(btn&&!lbl){
            btn->setFont(iconFontAlibaba);
            btn->setText((QChar)icon);
        }
    }
}

QPixmap IconHelper::getPixmap(const QColor &color, QString fontFamily, int icon, quint8 size, quint8 width, quint8 height)
{
    QFont font;
    if(fontFamily==FONT_WESOME_4){
        font = iconFontAwesome4;
    }else if(fontFamily==FONT_WETHER){
        font = iconFontWeather;
    }else if(fontFamily==FONT_ALBB){
        font = iconFontAlibaba;
    }

    QPixmap pix(width,height);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(color);

    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(pix.rect(), Qt::AlignCenter, (QChar)icon);

    painter.end();
    return pix;
}
