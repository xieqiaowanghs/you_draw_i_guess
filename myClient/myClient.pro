#-------------------------------------------------
#
# Project created by QtCreator 2019-10-13T13:14:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        answerwidget.cpp \
        client.cpp \
        gameover.cpp \
        gamereadywidget.cpp \
        gamingwidget.cpp \
        hallwidget.cpp \
        handler/gameoverhandler.cpp \
        handler/gamereadyhandler.cpp \
        handler/gaminghandler.cpp \
        handler/handler.cpp \
        handler/ihandler.cpp \
        handler/imagehandler.cpp \
        handler/loginhandler.cpp \
        handler/registerhandler.cpp \
        handler/roomhandler.cpp \
        loginwidget.cpp \
        main.cpp \
        painter/eraser.cpp \
        painter/ipainter.cpp \
        painter/mylabel.cpp \
        painter/paintcircle.cpp \
        painter/paintcurve.cpp \
        painter/painter.cpp \
        painter/paintline.cpp \
        painter/paintrectangle.cpp \
        questions.cpp

HEADERS += \
    answerwidget.h \
    client.h \
    gameover.h \
    gamereadywidget.h \
    gamingwidget.h \
    hallwidget.h \
    handler/gameoverhandler.h \
    handler/gamereadyhandler.h \
    handler/gaminghandler.h \
    handler/handler.h \
    handler/ihandler.h \
    handler/imagehandler.h \
    handler/loginhandler.h \
    handler/registerhandler.h \
    handler/roomhandler.h \
    loginwidget.h \
    painter/eraser.h \
    painter/ipainter.h \
    painter/mylabel.h \
    painter/paintcircle.h \
    painter/paintcurve.h \
    painter/painter.h \
    painter/paintline.h \
    painter/paintrectangle.h \
    protocol.h \
    questions.h \
    singleton.h

FORMS += \
    answerwidget.ui \
    gameover.ui \
    gamereadywidget.ui \
    gamingwidget.ui \
    hallwidget.ui \
    loginwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    questions.qrc
