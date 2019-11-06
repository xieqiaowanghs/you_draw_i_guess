#include "gameoverhandler.h"
#include <QJsonArray>
#include <QStringList>
#include "singleton.h"
#include "gameover.h"
#include "gamingwidget.h"
#include "answerwidget.h"
#include <QThread>

Gameoverhandler::Gameoverhandler()
{

}

void Gameoverhandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    QString type = protocol["type"].toString();

    if(type == "ranking")
    {
        QJsonArray rankArray = protocol["rankList"].toArray();
        QStringList ranks;

        SingleTon<AnswerWidget>::getInstance()->setPixmap();
        SingleTon<AnswerWidget>::getInstance()->show();
        SingleTon<AnswerWidget>::getInstance()->startTime();
        SingleTon<AnswerWidget>::getInstance()->setFlag(true);

//        QThread::sleep(3);
        int i;
        for(i = 0; i < rankArray.size(); ++i){
            ranks.append(rankArray[i].toString());
        }
        SingleTon<GameOver>::getInstance()->Showrank(ranks);

    }
}
