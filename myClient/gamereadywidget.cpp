#include "gamereadywidget.h"
#include "ui_gamereadywidget.h"

GameReadyWidget::GameReadyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameReadyWidget)
{
    ui->setupUi(this);

    btnIsReady = false;
    ui->btnReady->setText("准备游戏");

    ui->btnKickOutGamer1->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->btnKickOutGamer2->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->btnKickOutGamer3->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->btnKickOutGamer4->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->btnKickOutGamer5->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->btnKickOutGamer6->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
}

GameReadyWidget::~GameReadyWidget()
{
    delete ui;
}

void GameReadyWidget::setActiveUser(const QString &username)
{
    ui->lbActiveUser->setText("用户名:"+username);
}

int GameReadyWidget::getGamerNumb() const
{
    int count = 0;
    if(ui->lbGamer1->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;
    if(ui->lbGamer2->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;
    if(ui->lbGamer3->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;
    if(ui->lbGamer4->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;
    if(ui->lbGamer5->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;
    if(ui->lbGamer6->text().split(" ",QString::SkipEmptyParts).size() >= 2) count += 1;

    return count;
}

void GameReadyWidget::setLbGamerInfo(const QString &info, int num)
{
    switch (num) {
    case 1:
        ui->lbGamer1->setText(info);
        break;
    case 2:
        ui->lbGamer2->setText(info);
        break;
    case 3:
        ui->lbGamer3->setText(info);
        break;
    case 4:
        ui->lbGamer4->setText(info);
        break;
    case 5:
        ui->lbGamer5->setText(info);
        break;
    case 6:
        ui->lbGamer6->setText(info);
        break;
    default:
        break;
    }
}

void GameReadyWidget::clearAllLBGamer()
{
    ui->lbGamer1->clear();
    ui->lbGamer2->clear();
    ui->lbGamer3->clear();
    ui->lbGamer4->clear();
    ui->lbGamer5->clear();
    ui->lbGamer6->clear();
}

void GameReadyWidget::setLbGamerNotReady()
{
    if(ui->lbGamer1->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer1->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    ";
        ui->lbGamer1->setText(Info);
    }else if (ui->lbGamer1->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer1->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer1->setText(Info);
    }

    if(ui->lbGamer2->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer2->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    ";
        ui->lbGamer2->setText(Info);
    }else if (ui->lbGamer2->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer2->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer2->setText(Info);
    }

    if(ui->lbGamer3->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer3->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备   ";
        ui->lbGamer3->setText(Info);
    }else if (ui->lbGamer3->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer3->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer3->setText(Info);
    }
    if(ui->lbGamer4->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer4->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    ";
        ui->lbGamer4->setText(Info);
    }else if (ui->lbGamer4->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer4->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer4->setText(Info);
    }
    if(ui->lbGamer5->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer5->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    ";
        ui->lbGamer5->setText(Info);
    }else if (ui->lbGamer5->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer5->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer5->setText(Info);
    }
    if(ui->lbGamer6->text().split(" ",QString::SkipEmptyParts).size() == 2){
        QStringList string = ui->lbGamer6->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    ";
        ui->lbGamer6->setText(Info);
    }else if (ui->lbGamer6->text().split(" ",QString::SkipEmptyParts).size() == 3) {
        QStringList string = ui->lbGamer6->text().split(" ",QString::SkipEmptyParts);
        QString Info = string[0] + "    未准备    " + string[2];
        ui->lbGamer6->setText(Info);
    }

}

void GameReadyWidget::btnStartGameHideOrShow()
{
    if(this->MasterFlag) ui->btnStartGame->show();
    else ui->btnStartGame->hide();
}

void GameReadyWidget::btnKickGamerHideOrShow()
{
    if(this->MasterFlag){
        if(ui->lbGamer1->text().split(" ",QString::SkipEmptyParts).size() == 2){
            ui->btnKickOutGamer1->show();
            qDebug()<<ui->lbGamer1->text().split(" ",QString::SkipEmptyParts);
        }
        else ui->btnKickOutGamer1->hide();

        if(ui->lbGamer2->text().split(" ",QString::SkipEmptyParts).size() == 2){
            ui->btnKickOutGamer2->show();
            qDebug()<<ui->lbGamer1->text().split(" ",QString::SkipEmptyParts);
        }
        else ui->btnKickOutGamer2->hide();

        if(ui->lbGamer3->text().split(" ",QString::SkipEmptyParts).size() == 2) ui->btnKickOutGamer3->show();
        else ui->btnKickOutGamer3->hide();

        if(ui->lbGamer4->text().split(" ",QString::SkipEmptyParts).size() == 2) ui->btnKickOutGamer4->show();
        else ui->btnKickOutGamer4->hide();

        if(ui->lbGamer5->text().split(" ",QString::SkipEmptyParts).size() == 2) ui->btnKickOutGamer5->show();
        else ui->btnKickOutGamer5->hide();

        if(ui->lbGamer6->text().split(" ",QString::SkipEmptyParts).size() == 2) ui->btnKickOutGamer6->show();
        else ui->btnKickOutGamer6->hide();
    }else {
        ui->btnKickOutGamer1->hide();
        ui->btnKickOutGamer2->hide();
        ui->btnKickOutGamer3->hide();
        ui->btnKickOutGamer4->hide();
        ui->btnKickOutGamer5->hide();
        ui->btnKickOutGamer6->hide();
    }
}

void GameReadyWidget::appendText(const QString &message)
{
    ui->tbShow->append(message);
}

void GameReadyWidget::readyRoomInit()
{
    btnIsReady = false;
    ui->btnReady->setText("准备游戏");
}

void GameReadyWidget::on_btnReady_clicked()
{
    if(btnIsReady == false){
        //此时未准备,按钮显示为"准备游戏",按下后置btnIsReady为true,显示为"取消准备"
        btnIsReady = true;
        ui->btnReady->setText("取消准备");
        GameReadyHandler grh;
        grh.readyGameStart(username,roomName);
    }else {
        //此时已准备,按钮显示为"取消准备",按下后置btnIsReady为false,显示为"准备游戏"
        btnIsReady = false;
        ui->btnReady->setText("准备游戏");
        GameReadyHandler grh;
        grh.readyGameStartCancel(username,roomName);
    }
}


void GameReadyWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
    RoomHandler rh;
    rh.exitRoom(this->username,this->roomName,MasterFlag);

    ui->tbShow->clear();
    ui->lbGamer1->clear();
    ui->lbGamer2->clear();
    ui->lbGamer3->clear();
    ui->lbGamer4->clear();
    ui->lbGamer5->clear();
    ui->lbGamer6->clear();
    ui->btnReady->setText("准备游戏");
    this->btnIsReady = false;
    this->MasterFlag = false;
    this->btnStartGameHideOrShow();

    SingleTon<HallWidget>::getInstance()->show();
}

void GameReadyWidget::on_leInput_returnPressed()
{
    QString message = ui->leInput->text();
    if(message.isEmpty()) return;

    GameReadyHandler grh;
    grh.Chat(username,roomName,message);
//    qDebug()<<message;
    ui->leInput->clear();
}

void GameReadyWidget::on_btnStartGame_clicked()
{
    if(this->getGamerNumb() == 1 && ui->lbGamer1->text().split(" ",QString::SkipEmptyParts)[1] == "已准备"){
        QMessageBox::warning(this,"warning","一个人不能开始游戏");
        return;
    }else if(this->getGamerNumb() == 1 && ui->lbGamer1->text().split(" ",QString::SkipEmptyParts)[1] == "未准备"){
        return;
    }
    GameReadyHandler grh;
    grh.gameStart(this->username,this->roomName);
}

void GameReadyWidget::on_btnKickOutGamer1_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer1->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}

void GameReadyWidget::on_btnKickOutGamer2_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer2->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}

void GameReadyWidget::on_btnKickOutGamer3_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer3->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}

void GameReadyWidget::on_btnKickOutGamer4_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer4->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}

void GameReadyWidget::on_btnKickOutGamer5_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer5->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}

void GameReadyWidget::on_btnKickOutGamer6_clicked()
{
    QMessageBox::StandardButton result = QMessageBox::question(this,"确认提示","确定将该用户踢出房间吗",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Yes);
    if(result == QMessageBox::Yes){
        GameReadyHandler grh;
        grh.KickOutGamer(ui->lbGamer6->text().split(" ",QString::SkipEmptyParts)[0],this->roomName);
    }else if (result == QMessageBox::Cancel) {
        return;
    }
}
