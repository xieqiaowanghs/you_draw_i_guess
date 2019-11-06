#ifndef GAMEREADYWIDGET_H
#define GAMEREADYWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

#include "hallwidget.h"
#include "handler/roomhandler.h"
#include "handler/gamereadyhandler.h"

#define N 6

namespace Ui {
class GameReadyWidget;
}

class GameReadyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameReadyWidget(QWidget *parent = nullptr);
    ~GameReadyWidget();

    inline void setRoomName(const QString& roomName) {this->roomName = roomName;}
    inline QString getRoomName()const {return this->roomName;}

    inline void setMasterFlag(bool value) {this->MasterFlag = value;}
    inline bool getMasterFlag()const {return this->MasterFlag;}

    inline void setUsername(const QString& username) {this->username = username;}
    inline QString getUsername()const {return this->username;}

    void setActiveUser(const QString& username);//在用户名标签上设置用户名
    int getGamerNumb()const;//得知准备界面中有多少人

    void setLbGamerInfo(const QString& info,int num);//设置用户信息(名字+状态+是否房主)
    void clearAllLBGamer();//清空所有玩家标签
    void setLbGamerNotReady();

    void btnStartGameHideOrShow();
    void btnKickGamerHideOrShow();

    void appendText(const QString& message);
    void readyRoomInit();

private slots:
    void on_btnReady_clicked();

    void on_leInput_returnPressed();

    void on_btnStartGame_clicked();

    void on_btnKickOutGamer1_clicked();

    void on_btnKickOutGamer2_clicked();

    void on_btnKickOutGamer3_clicked();

    void on_btnKickOutGamer4_clicked();

    void on_btnKickOutGamer5_clicked();

    void on_btnKickOutGamer6_clicked();

private:
    Ui::GameReadyWidget *ui;

    bool btnIsReady;//进入准备房间,构造函数默认为false
    bool MasterFlag;
    QString roomName;
    QString username;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // GAMEREADYWIDGET_H
