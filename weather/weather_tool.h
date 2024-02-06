#ifndef WEATHER_TOOL_H
#define WEATHER_TOOL_H

#include <QHash>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QJsonParseError>

class Weather_Tool{
private:
    static  QHash<QString ,QString> m_city_code_hash;

    static void InitCityCode(){
        //读取citycode.json，写到hash里面
        QFile file("E:/Qtcode/weather/citycode.json");
        file.open(QFile::ReadOnly|QIODevice::Text);
        QByteArray jsonarray = file.readAll();
        file.close();

        QJsonParseError err;
        QJsonDocument doc=QJsonDocument::fromJson(jsonarray,&err);
        if(err.error!=QJsonParseError:: NoError){
            return;
        }

        QJsonArray citys=doc.array();
        for(int i=0;i<citys.size();++i)
        {
           QString  cityname=citys[i].toObject().value("city_name").toString();
           QString citycode=citys[i].toObject().value("city_code").toString();
           if(citycode.isEmpty()){
               continue;
           }
           m_city_code_hash.insert(cityname,citycode);
        }
    }
public:
    static QString SetCityCode(QString city_name){ //根据城市名拿到对应编号
        if(m_city_code_hash.isEmpty()){
            InitCityCode();
        }

        auto it=m_city_code_hash.find(city_name);

        if(it==m_city_code_hash.end()){
            city_name+="市";  //比如搜西安， json文件里面是西安市，所以再搜一遍
            it=m_city_code_hash.find(city_name);
            if(it==m_city_code_hash.end()){
                return "";
            }
        }
        return it.value();

    }

};

QHash<QString ,QString> Weather_Tool::m_city_code_hash{};

#endif // WEATHER_TOOL_H
