#include "handler.h"
#include "ihandler.h"
#include "registerhandler.h"
#include "loginhandler.h"
#include "roomhandler.h"
#include "gamereadyhandler.h"
#include "gaminghandler.h"
#include "gameoverhandler.h"
#include "imagehandler.h"

Handler::Handler()
{

}

void Handler::Handle(QTcpSocket *Socket, const Protocol &protocol)
{
    IHandler* handler = nullptr;
    switch(protocol.getType()){
    case Protocol::login:
        handler = new LoginHandler;
        break;
    case Protocol::regist:
        handler = new RegisterHandler;
        break;
    case Protocol::room:
        handler = new RoomHandler;
        break;
    case Protocol::readyGame:
        handler = new GameReadyHandler;
        break;
    case Protocol::gaming:
        handler = new GamingHandler;
        break;
    case Protocol::gameover:
        handler = new Gameoverhandler;
        break;
    case Protocol::none:
        break;
    case Protocol::image:
        handler = new ImageHandler;
        break;
    }

    if(handler != nullptr){
        handler->handle(Socket, protocol);
        delete handler;
    }
}
