#include "answerwidget.h"
#include "ui_answerwidget.h"
#include <QCloseEvent>
#include "gamingwidget.h"
#include "singleton.h"
#include <QDebug>
#include <gameover.h>
#include <QMovie>

AnswerWidget::AnswerWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerWidget),
    flag(false)
{
    ui->setupUi(this);

}

AnswerWidget::~AnswerWidget()
{
    delete ui;
}

void AnswerWidget::changePixmap(QPixmap pix)
{
    pixmap = pix;
}

void AnswerWidget::setPixmap()
{
    QPixmap scaledPixmap;
    scaledPixmap = pixmap.scaled(ui->lbFinal->size());
    ui->lbFinal->setPixmap(scaledPixmap);
    QString question = "题目： " + SingleTon<GamingWidget>::getInstance()->getTitleName();
    ui->lbTitle->setText(question);
    QString painter = "画家： " + SingleTon<GamingWidget>::getInstance()->getPainter();
    ui->lbPainter->setText(painter);
}

void AnswerWidget::startTime()
{
    startTimer(2600);

}

void AnswerWidget::setFlag(bool value)
{
    flag = value;
}

void AnswerWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void AnswerWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    if(movie != nullptr){
        movie->stop();
        movie->deleteLater();
        ui->lbTip->clear();
    }

    this->hide();
    if(flag)
        SingleTon<GameOver>::getInstance()->show();
}

void AnswerWidget::showEvent(QShowEvent *)
{
    movie = new QMovie(":/loading.gif");
    movie->setScaledSize(ui->lbFinal->size());
    ui->lbTip->setMovie(movie);
    movie->start();
    ui->lbFinal->show();
}
