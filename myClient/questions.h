#ifndef QUESTIONS_H
#define QUESTIONS_H

/**
 * questions.h
 * 作者:骆正琛
 * 作用:读取题库文件以及提供相关接口函数
 */
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QString>

class Questions
{
    QVector<QVector<QString>> questions;

public:
    Questions();
    bool readDataFromFile();  //读文件

    bool getAnswerValidity(int id, QString answerName);  //判断回答是否正确
    QString getQuestionFromID(int id);   //通过从服务端发来的ID 从vector中获取题目
    QString getClue(int id, int times);    //获得提示
};

#endif // QUESTIONS_H
