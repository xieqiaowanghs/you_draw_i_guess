#include "gameover.h"
#include "ui_gameover.h"
#include "singleton.h"
#include <QCloseEvent>
#include "gamereadywidget.h"
#include "gamingwidget.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::closeEvent(QCloseEvent *event)
{
    event->accept();
    SingleTon<GameReadyWidget>::getInstance()->show();
    SingleTon<GamingWidget>::getInstance()->hide();

}

void GameOver::Showrank(const QStringList &rankList)//显示积分排名
{
    ui->lbOver->clear();
    ui->lbOver->addItems(rankList);
}

