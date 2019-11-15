#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;
    s.initServer("127.0.0.1",7000);
    return a.exec();
}
