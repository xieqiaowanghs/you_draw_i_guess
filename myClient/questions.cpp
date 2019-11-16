#include "questions.h"

/**
 * questions.cpp
 * 作者:骆正琛
 * 作用:读取题库文件以及提供相关接口函数
 */

Questions::Questions()
{
    readDataFromFile();
}

bool Questions::readDataFromFile()
{
    QFile file(":/questions.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QVector<QString> question;

    QTextStream stream(&file);
    while(!file.atEnd())
    {
        QString buf;
        QStringList list = stream.readAll().split("\n");
        QListIterator<QString> li(list);

        while(li.hasNext())
        {
            buf=li.next();
            QString buf2;
            QStringList list2 = buf.split(" ");
            QListIterator<QString> li2(list2);
            while(li2.hasNext())
            {
                buf2 = li2.next();
                question.append(buf2);
            }
            questions.append(question);
            question.clear();
        }
    }
    file.close();

  // qDebug()<<questions;
   return true;
}

bool Questions::getAnswerValidity(int id, QString answerName)
{
    QString questionName = getQuestionFromID(id);
    if(answerName == questionName)
    {
        return true;
    }
    return false;
}

QString Questions::getQuestionFromID(int id)
{
    qDebug()<<"getid"<<id;
    QString questionName = questions.at(id).at(1);
    qDebug()<<questionName;
    return questionName;
}

QString Questions::getClue(int id, int times)
{
    QString clue = questions.at(id).at(times + 2);
    qDebug()<<clue;
    return clue;
}




