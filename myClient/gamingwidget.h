#ifndef GAMINGWIDGET_H
#define GAMINGWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>

namespace Ui {
class GamingWidget;
}

class GamingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamingWidget(QWidget *parent = nullptr);
    ~GamingWidget();

    void setPixmap(const QPixmap& pixmap);
    void setRoomName(const QString& value);  //修改
    void appendText(const QString& message);

    inline QString getRoomName() {return roomName;}
    inline QString getTitleName() const{return titleName;}
    inline void setTitleName(const QString &value){titleName = value;}
    inline int getClueCount(){return clueCount;}
    inline void setClueCount(int value){clueCount = value;}
    inline void  setID(const int &value){id = value;}
    inline int getID(){return id;}
    inline void setPainter(QString value){painter = value;}
    inline QString getPainter(){return painter;}

    bool isTitlePlayed(int id); //判断是否玩过
    void nextCount(); //下一回合
    void initGame();
    QString nextClue(int id);


    void countDown();//聂
    void stopCountDown();
    void setLbGamerInfo(const QString& info,int num);//设置用户信息(名字+积分+是否画手)  聂
    QLabel* getSpecifiedLabel(int num);
    void painterCantsend();
    void disable();//谢  绘画权限
    void enable();
    QPixmap getPixmap()const;
private slots:
    void on_leInput_returnPressed();

    void on_btnColor_clicked();

    void on_rbtnThin_clicked();

    void on_rbtnMiddle_clicked();

    void on_rbtnHeavy_clicked();

    void on_btnPen_clicked();

    void on_btnRubber_clicked();

    void on_btnClear_clicked();

private:
      Ui::GamingWidget *ui;

    QString roomName;
    int id; //当前题目id
    QString titleName; //当前回合题目
    int clueCount; //第几条提示
    QString painter;

    int timeCountDown;
    QTimer* timer;

    // QWidget interface
protected:

    // QWidget interface
protected:
    void hideEvent(QHideEvent *event);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // GAMINGWIDGET_H
