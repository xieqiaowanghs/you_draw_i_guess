#include "imagehandler.h"
#include "answerwidget.h"

ImageHandler::ImageHandler()
{

}

void ImageHandler::sendPicture(const QString &username, const QString &roomName, const QByteArray& bytes)
{
   Protocol p(Protocol::image);
   p["username"] = username;
   p["roomName"] = roomName;
   //编码转化为QString
   QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
   QString image = codec->toUnicode(bytes);
   p["image"] = image;

   SingleTon<QTcpSocket>::getInstance()->write(p.pack());
}

void ImageHandler::handle(QTcpSocket *socket, const Protocol &protocol)
{
    //string 转成图片
    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    QString string = protocol["image"].toString();
    QByteArray b = codec->fromUnicode(string);
    QBuffer buffer(&b);
    QImage image;
    image.load(&buffer,"jpg");
    QPixmap pixmap = QPixmap::fromImage(image);
    SingleTon<GamingWidget>::getInstance()->setPixmap(pixmap);//自定义接口
    SingleTon<AnswerWidget>::getInstance()->changePixmap(pixmap);
}
