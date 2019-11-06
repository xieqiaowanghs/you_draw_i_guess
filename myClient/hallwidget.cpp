#include "hallwidget.h"
#include "ui_hallwidget.h"
#include "handler/loginhandler.h"
#include "handler/roomhandler.h"

HallWidget::HallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HallWidget)
{
    ui->setupUi(this);

    flushTimer = new QTimer(this);
    QObject::connect(flushTimer,&QTimer::timeout,this,[=](){
        RoomHandler rh;
        rh.flushRoom();
    });


    flushTimer->start(1000);
}

HallWidget::~HallWidget()
{
    delete ui;
    flushTimer->deleteLater();
}

void HallWidget::setUsername(const QString &username)
{
    ui->lbUsername->setText(username);
}

void HallWidget::flushRoom(const QStringList &roomList)
{
    ui->lwRoom->clear();
    ui->lwRoom->addItems(roomList);
}

void HallWidget::closeEvent(QCloseEvent *)
{
    LoginHandler lh;
    lh.quit(ui->lbUsername->text());
}

void HallWidget::on_btnCreateRoom_clicked()
{
    bool ok;//接收按钮返回值
    QString roomName = QInputDialog::getText(this,"请输入房间名","房间名",QLineEdit::Normal,QString(),
                                             &ok,Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    if(ok && roomName.length() == 0){
        QMessageBox::warning(nullptr,"警告","用户名不能为空");
        return;
    }
    if(!ok) return;
    RoomHandler rh;
    rh.createRoom(ui->lbUsername->text(),roomName);
}


void HallWidget::showEvent(QShowEvent *)
{
    RoomHandler rh;
    rh.flushRoom();
}

void HallWidget::on_lwRoom_itemDoubleClicked(QListWidgetItem *item)
{
    QString roomInfo = item->text();
    if(roomInfo.split(" ",QString::SkipEmptyParts).size() > 2){
        QMessageBox::information(nullptr,"提示","不能加入已经开始游戏的房间");
        return;
    }

    QString roomName = roomInfo.split(" ",QString::SkipEmptyParts)[0];
    QString username = ui->lbUsername->text();
//    qDebug()<<roomName;

    RoomHandler rh;
    rh.joinRoom(roomName, username);
}

void HallWidget::on_btnFlush_clicked()
{
    RoomHandler rh;
    rh.flushRoom();
}
