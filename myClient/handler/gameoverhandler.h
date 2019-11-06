#ifndef GAMEOVERHANDLER_H
#define GAMEOVERHANDLER_H

#include "ihandler.h"

class Gameoverhandler :public IHandler
{
public:
    Gameoverhandler();

    void handle(QTcpSocket *socket, const Protocol &protocol);
};

#endif // GAMEOVERHANDLER_H
