#include "gaminghandler.h"
#include "singleton.h"
#include "gamingwidget.h"
#include "gamereadyhandler.h"
#include "answerwidget.h"
#include <QThread>

GamingHandler::GamingHandler()
{

}

void GamingHandler::gameOver(const QString &roomName)//发送游戏结束信号
{
    Protocol protocol(Protocol::gameover);
    protocol["type"] = "gameover";
    protocol["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void GamingHandler::getQuestionIDFromServer(const QString &roomName, const QString username)
{
    Protocol protocol(Protocol::gaming);
    protocol["type"] = "getQuestionIDFromServer";
    protocol["roomName"] = roomName;
    protocol["username"] = username;
    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void GamingHandler::sendAnswer(const QString &roomName, const QString username, const QString message)
{
    QString titleName = SingleTon<GamingWidget>::getInstance()->getTitleName();

    Protocol protocol(Protocol::gaming);
    protocol["type"] = "sendAnswer";
    protocol["roomName"] = roomName;
    protocol["username"] = username;
    if(titleName == message)
    {
        protocol["true"] = "T";
    }
    else {
        protocol["true"] = "F";
        protocol["message"] = message;
    }
    SingleTon<QTcpSocket>::getInstance()->write(protocol.pack());
}

void GamingHandler::OneRoundOfGameTimingEnds(const QString &roomName)
{
    Protocol p(Protocol::gaming);
    p["type"] = "OneRoundOfGameTimingEnds";
    p["roomName"] = roomName;

    SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void GamingHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();
    if(type == "getQuestionIDFromServer")
    { 
        /** 服务端获得id*/
        int id = protocol["id"].toInt();
        if(id < 0)
        {
            qDebug()<<"题库空了";
        }
        else {
            QString painter = protocol["painter"].toString();
            SingleTon<GamingWidget>::getInstance()->setID(id);
            SingleTon<GamingWidget>::getInstance()->setPainter(painter);
            SingleTon<GamingWidget>::getInstance()->nextCount();  
        }

    }
    else if(type == "sendAnswer"){
        qDebug()<<"send";
        QString message = protocol["message"].toString();
        QString judge = protocol["judge"].toString();
        SingleTon<GamingWidget>::getInstance()->appendText(message);
        qDebug()<<"judge:"<<judge;
        if(judge == "T")
        {
            QString state = protocol["state"].toString();
            QJsonArray userArray = protocol["userList"].toArray();

            for (int i = 0;i < userArray.size();i++) {
                SingleTon<GamingWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
            }

            qDebug()<<"state: "<<state;
            if(state == "nextCount")
            {
                qDebug()<<"调用回合结束界面";

                SingleTon<AnswerWidget>::getInstance()->setPixmap();
                SingleTon<AnswerWidget>::getInstance()->show();
                SingleTon<AnswerWidget>::getInstance()->startTime();

                //测试
                QString painter = protocol["painter"].toString();
                SingleTon<GamingWidget>::getInstance()->stopCountDown();
                SingleTon<GamingWidget>::getInstance()->appendText("\n\n下一轮游戏开始\n\n");
                SingleTon<GamingWidget>::getInstance()->setPainter(painter);
                SingleTon<GamingWidget>::getInstance()->countDown();
                SingleTon<GamingWidget>::getInstance()->initGame();
            }else if (state == "gameOver") {
                qDebug()<<"游戏结束 调用结束界面 time";
                ////////////
                SingleTon<GamingWidget>::getInstance()->stopCountDown();
                QString roomName = SingleTon<GamingWidget>::getInstance()->getRoomName();
                QString painter = SingleTon<GamingWidget>::getInstance()->getPainter();
                QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
                if(painter == username)
                {
                    gameOver(roomName);
                }
            }
        }
    }else if(type == "OneRoundOfGameTimingEnds")
    {
        QString state = protocol["state"].toString();
        QJsonArray userArray = protocol["userList"].toArray();

        for (int i = 0;i < userArray.size();i++) {
            SingleTon<GamingWidget>::getInstance()->setLbGamerInfo(userArray[i].toString(),i+1);
        }
        qDebug()<<"state: "<<state;
        if(state == "nextCount")
        {
            qDebug()<<"调用回合结束界面 time";
            //测试
            QString painter = protocol["painter"].toString();
            SingleTon<GamingWidget>::getInstance()->setPainter(painter);
            SingleTon<GamingWidget>::getInstance()->countDown();
            SingleTon<GamingWidget>::getInstance()->appendText("\n\n下一轮游戏开始\n\n");
            SingleTon<GamingWidget>::getInstance()->initGame();
        }else if (state == "gameOver") {
            qDebug()<<"游戏结束 调用结束界面 time";
            QString roomName = SingleTon<GamingWidget>::getInstance()->getRoomName();
            QString painter = SingleTon<GamingWidget>::getInstance()->getPainter();
            QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
            if(painter == username)
            {
                gameOver(roomName);
            }
        }
    }else if(type == "setPainter"){
        QString painter = protocol["painter"].toString();
        QString username = SingleTon<GameReadyWidget>::getInstance()->getUsername();
        if(username == painter){
            SingleTon<GamingWidget>::getInstance()->enable();
        }else {
            SingleTon<GamingWidget>::getInstance()->disable();
        }

    }
}
