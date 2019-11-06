#ifndef GAMEOVERHANDLER_H
#define GAMEOVERHANDLER_H

#include "ihandler.h"
#include "room/roommanager.h"
#include "singleton.h"
#include <QJsonArray>

class GameoverHandler : public IHandler
{
public:
    GameoverHandler();

    // IHandler interface
public:
    void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // GAMEOVERHANDLER_H
