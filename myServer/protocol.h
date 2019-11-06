#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class Protocol{
public:
    enum Type{
        none = 0,
        regist,
        login,
        room,
        readyGame,
        gaming,
        gameover,
        image
    };

    Protocol(Type type = none):type(type){}

    inline void setType(Type type){this->type = type;}
    inline Type getType()const{return this->type;}

    inline QJsonValue operator[](const QString& key)const{return object[key];}
    inline QJsonValueRef operator[](const QString& key){return object[key];}

    QByteArray pack(){
        QByteArray body = QJsonDocument(object).toJson();

        QByteArray head(8, 0);
        *(int*)(head.data()) = body.size();
        *(Type*)(head.data() + 4) = type;

        return head + body;
    }

    int unpack(const QByteArray& array){
        if(array.size() < 8)    return 0;

        int len = *(int*)(array.data());
        Type type = *(Type*)(array.data() + 4);

        if(array.size() < 8 + len)  return 0;

        QJsonObject object = QJsonDocument::fromJson(array.mid(8, len)).object();
        if(object.isEmpty() && len > 0) return 0;

        this->type = type;
        this->object = object;

        return 8 + len;
    }

private:
    Type type;
    QJsonObject object;
};

#endif // PROTOCOL_H
