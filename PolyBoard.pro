######################################################################
# Automatically generated by qmake (3.1) Sun Apr 5 17:01:14 2020
######################################################################

TEMPLATE = app
TARGET = PolyBoard
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += colore.h \
           model/gioco.h \
           pedina/id.h \
           posizione.h \
           model/scacchi.h \
           model/scacchiera.h \
           view/chessbutton.h \
           view/mainwindow.h \
           pedina/pedina.h \
           pedina/scacchi/alfiere.h \
           pedina/scacchi/cavallo.h \
           pedina/scacchi/pedinascacchi.h \
           pedina/scacchi/pedone.h \
           pedina/scacchi/re.h \
           pedina/scacchi/regina.h \
           pedina/scacchi/torre.h \
           pedina/scacchi/movimentoCroce.h \
           pedina/scacchi/movimentoDiagonale.h \
           view/selettore_gioco.h \
           controller.h \
           tipogioco.h \
           view/selettore_promozione_scacchi.h
SOURCES += \
           model/gioco.cpp \
           pedina/id.cpp \
           posizione.cpp \
           model/scacchi.cpp \
           model/scacchiera.cpp \
           main.cpp \
           view/chessbutton.cpp \
           view/mainwindow.cpp \
           pedina/pedina.cpp \
           pedina/scacchi/alfiere.cpp \
           pedina/scacchi/cavallo.cpp \
           pedina/scacchi/pedinascacchi.cpp \
           pedina/scacchi/pedone.cpp \
           pedina/scacchi/re.cpp \
           pedina/scacchi/regina.cpp \
           pedina/scacchi/torre.cpp \
           pedina/scacchi/movimentoCroce.cpp \
           pedina/scacchi/movimentoDiagonale.cpp \
           view/selettore_gioco.cpp \
           controller.cpp \
           tipogioco.cpp \
           view/selettore_promozione_scacchi.cpp \
           colore.cpp

QT += widgets

RESOURCES += \
    resources.qrc
