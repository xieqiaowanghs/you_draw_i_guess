#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "handler/registerhandler.h"
#include "handler/loginhandler.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

QString LoginWidget::getLastUsername()
{
    return this->username;
}

void LoginWidget::on_btnRegister_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    if(username.isEmpty() || password.isEmpty())    return;

    ui->leUsername->clear();
    ui->lePassword->clear();

    //注册
    RegisterHandler rh;
    rh.regist(username, password);
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    if(username.isEmpty() || password.isEmpty())    return;

    ui->leUsername->clear();
    ui->lePassword->clear();

    //登录
    LoginHandler lh;
    lh.login(username, password);

    this->username = username;
}
