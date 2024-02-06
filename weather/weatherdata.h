#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>


class Today{
public :
    QString data;
    QString city;
    QString testdata;

    int wendu;
    QString shidu;
    int pm25;
    QString quality;

    QString type;

    QString fx;
    QString fl;

    int high;
    int low;
    Today():data("2024-2-03"),city("昆明"),testdata("今天适合所有人出门"),wendu(15),
        shidu("40%"),pm25(3),quality("优"),type("多云"),fx("南风"),fl("3级"),
        high(21),low(-5){}
};


class Day{
public:
    QString data;
    QString week;

    QString type;

    QString fx;
    QString fl;

    int high;
    int low;

    int aqi;
    Day():data("2-03"),week("周五"),type("多云"),fx("南风"),fl("3级"),high(21),low(-5),aqi(0){}
};

#endif // WEATHERDATA_H
