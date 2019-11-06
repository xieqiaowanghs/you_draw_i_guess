#include "gamingwidget.h"
#include "ui_gamingwidget.h"
#include "handler/gaminghandler.h"
#include "questions.h"
#include "gamereadywidget.h"
#include "answerwidget.h"
#include "answerwidget.h"

#include <QString>
#include <QDebug>
#include <QColorDialog>
#include <QCloseEvent>
/**
 * 文件名 GamingWidget.cpp
 * 作者： 骆正琛
 * 功能： 游戏界面
 *
 */

GamingWidget::GamingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamingWidget)
{
    ui->setupUi(this);

    QString roomName = SingleTon<GameReadyWidget>::getInstance()->getRoomName();
    setRoomName(roomName);

    ui->lbShow->init();
    ui->rbtnThin->setChecked(true);
    ui->lbColor->setStyleSheet("background-color:black");
    disable();
}

GamingWidget::~GamingWidget()
{
    delete ui;
}

void GamingWidget::setPixmap(const QPixmap &pixmap)
{
    ui->lbShow->setPixmap(pixmap);
}

void GamingWidget::nextCount()
{

   // qDebug()<<id;
    painterCantsend();
    Questions qu;
    setTitleName(qu.getQuestionFromID(id));
    //qDebug()<<"title"<<titleName;
    QString clueName = nextClue(id);
    QString tip = "提示： " + clueName;
    QString question = "题目： " + titleName;
    if(SingleTon<GameReadyWidget>::getInstance()->getUsername() == painter){
        ui->lbTip->setText(question);
    }else{
        ui->lbTip->setText(tip);
    }
        //每轮开始初始化
    //SingleTon<AnswerWidget>::getInstance()->setPixmap();
    ui->lbShow->init();
}

void GamingWidget::initGame()
{
    SingleTon<AnswerWidget>::getInstance()->setFlag(false);
    setTitleName("题目");
    setClueCount(0);
   // qDebug()<<"init game";
    QString username = SingleTon<GameReadyWidget> ::getInstance()->getUsername();
    GamingHandler gh;
    gh.getQuestionIDFromServer(roomName, username);

}

QString GamingWidget::nextClue(int id)
{
    qDebug()<<"下条线索";
    Questions qu;
    QString clueName = qu.getClue(id,getClueCount());
    setClueCount(getClueCount() + 1);
    return clueName;
}

void GamingWidget::countDown()
{
    timeCountDown = 60;
    ui->lbTime->setText("时间:" + QString::number(timeCountDown));
    timer = new QTimer;
    QObject::connect(timer,&QTimer::timeout,this,[=](){
        timeCountDown--;
        ui->lbTime->setText("时间:" + QString::number(timeCountDown));
        if(timeCountDown == 0){
            if(SingleTon<GameReadyWidget>::getInstance()->getUsername() == painter){
                    /** 如果用户名等于画手的用户名,则计时结束发送计时结束的包*/
                    GamingHandler gh;
                    gh.OneRoundOfGameTimingEnds(roomName);
            }

            ui->lbTime->clear();
            timer->stop();
            timer->deleteLater();
        }
        if(timeCountDown == 30){
            if(SingleTon<GameReadyWidget>::getInstance()->getUsername() != painter){
                QString tip = nextClue(id);
                tip = ui->lbTip->text() + "    " + tip;
                ui->lbTip->setText(tip);
            }

        }
    });
    timer->start(1000);
}

void GamingWidget::stopCountDown()
{
    ui->lbTime->clear();
    timer->stop();
    timer->deleteLater();
}

void GamingWidget::setLbGamerInfo(const QString &info, int num)
{
    switch (num) {
    case 1:
        ui->lbGame1->setText(info);
        break;
    case 2:
        ui->lbGame2->setText(info);
        break;
    case 3:
        ui->lbGame3->setText(info);
        break;
    case 4:
        ui->lbGame4->setText(info);
        break;
    case 5:
        ui->lbGame5->setText(info);
        break;
    case 6:
        ui->lbGame6->setText(info);
        break;
    default:
        break;
    }
}

QLabel *GamingWidget::getSpecifiedLabel(int num)
{
    switch (num) {
    case 1:
        return ui->lbGame1;
    case 2:
        return ui->lbGame2;
    case 3:
        return ui->lbGame3;
    case 4:
        return ui->lbGame4;
    case 5:
        return ui->lbGame5;
    case 6:
        return ui->lbGame6;
    default:
        break;
    }
    return nullptr;
}

void GamingWidget::painterCantsend()
{
    if(painter == SingleTon<GameReadyWidget>::getInstance()->getUsername()){
        ui->leInput->hide();
    }else {
        ui->leInput->show();
    }
}

void GamingWidget::disable()
{
    //ui->lbShow->clear();
    //ui->lbShow->init();
    ui->lbShow->choosePaint("敲你吗");
    ui->lbShow->setCursor(Qt::ArrowCursor);
    ui->btnPen->setEnabled(false);
    ui->btnClear->setEnabled(false);
    ui->btnRubber->setEnabled(false);
    ui->lbShow->clear();
}

void GamingWidget::enable()
{
    ui->btnPen->setEnabled(true);
    ui->btnClear->setEnabled(true);
    ui->btnRubber->setEnabled(true);
    on_btnPen_clicked();
}

QPixmap GamingWidget::getPixmap() const
{
    return *(ui->lbShow->pixmap());
}

void GamingWidget::on_leInput_returnPressed()
{
    QString message = ui->leInput->text();
    if(message.isEmpty())   return;

    GamingHandler gh;
    QString username = SingleTon<GameReadyWidget> ::getInstance()->getUsername();
    gh.sendAnswer(roomName, username, message);
    ui->leInput->clear();
}


void GamingWidget::setRoomName(const QString &value)
{
    roomName = value;
    QString name = "你画我猜 房间名：" + roomName + "   用户名：" + SingleTon<GameReadyWidget>::getInstance()->getUsername();
    this->setWindowTitle(name);
}

void GamingWidget::appendText(const QString &message)
{
    ui->tbShow->append(message);
}

void GamingWidget::on_btnPen_clicked()
{
    ui->lbShow->choosePaint("曲线");
    ui->lbShow->setCursor(Qt::CrossCursor);
}

void GamingWidget::on_btnRubber_clicked()
{
    ui->lbShow->choosePaint("橡皮");
    //QCursor myCursor = QCursor(QPixmap(""),-1,-1);
    ui->lbShow->setCursor(Qt::OpenHandCursor);
}

void GamingWidget::on_btnClear_clicked()
{
    //ui->lbShow->clear();
    ui->lbShow->init();
    ui->lbShow->setCursor(Qt::ArrowCursor);
}

void GamingWidget::hideEvent(QHideEvent *event)
{
    ui->leInput->clear();
    ui->tbShow->clear();
    ui->lbGame1->clear();
    ui->lbGame2->clear();
    ui->lbGame3->clear();
    ui->lbGame4->clear();
    ui->lbGame5->clear();
    ui->lbGame6->clear();
    on_btnClear_clicked();
    //painter = "";
}

void GamingWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void GamingWidget::on_rbtnHeavy_clicked()
{
    ui->lbShow->setSize(7);
}

void GamingWidget::on_rbtnMiddle_clicked()
{
     ui->lbShow->setSize(4);
}

void GamingWidget::on_rbtnThin_clicked()
{
     ui->lbShow->setSize(1);
}

void GamingWidget::on_btnColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    ui->lbShow->setPenColor(color);
    ui->lbColor->setStyleSheet("background-color: rgb("+QString::number(color.red())+","+
                               QString::number(color.green())+","+QString::number(color.blue())+")");

}
