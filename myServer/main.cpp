#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;
    s.initServer("192.168.1.227",7000);
    return a.exec();
}
