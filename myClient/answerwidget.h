#ifndef ANSWERWIDGET_H
#define ANSWERWIDGET_H

#include <QDialog>

namespace Ui {
class AnswerWidget;
}

class AnswerWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AnswerWidget(QWidget *parent = nullptr);
    ~AnswerWidget();

    void changePixmap(QPixmap pix);
    void setPixmap();
    void startTime();
    void setFlag(bool value);

private:
    Ui::AnswerWidget *ui;
    QPixmap pixmap;
    bool flag;
    QMovie *movie;
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);

    // QWidget interface
protected:
    void showEvent(QShowEvent *event);
};

#endif // ANSWERWIDGET_H
