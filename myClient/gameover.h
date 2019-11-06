#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    void Showrank(const QStringList &ranklist);//显示结算积分排名
    ~GameOver();

private:
    Ui::GameOver *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // GAMEOVER_H
