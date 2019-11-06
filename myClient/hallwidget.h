#ifndef HALLWIDGET_H
#define HALLWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class HallWidget;
}

class HallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HallWidget(QWidget *parent = 0);
    ~HallWidget();

    void setUsername(const QString& username);

    void flushRoom(const QStringList& roomList);

private:
    Ui::HallWidget *ui;

    QTimer *flushTimer;

    // QWidget interface
private slots:
    void on_btnCreateRoom_clicked();

    void on_lwRoom_itemDoubleClicked(QListWidgetItem *item);

    void on_btnFlush_clicked();


protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent(QShowEvent *event);
};

#endif // HALLWIDGET_H
