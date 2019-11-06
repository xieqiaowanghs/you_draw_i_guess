#include "imagehandler.h"

ImageHandler::ImageHandler()
{

}

void ImageHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    //QString type = protocol["type"].toString();
    QString username = protocol["username"].toString();
    QString roomName = protocol["roomName"].toString();
    QString string = protocol["image"].toString();
    Protocol image(Protocol::image);
    image["image"] = string;
    Room* room = SingleTon<RoomManager>::getInstance()->selectRoom(roomName);
    if(room == nullptr) return;

    QVector<User>& users = room->allUsers();
    for (int i = 0;i < users.size();i++) {
        if(users[i].getUsername() != username){
            users[i].getSocket()->write(image.pack());
        }
    }
}
