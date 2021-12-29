QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include/"
#LIBS      += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win64"

INCLUDEPATH += $$PWD/inc

SOURCES += \
    src/HumanAction.cpp \
    src/GameController.cpp \
    src/GameUI.cpp \
    src/Fiar.cpp \
    src/FiarMove.cpp \
    src/Human.cpp \
    src/IA.cpp \
    src/MctsAlgorithm.cpp \
    src/MinMaxAlgorithm.cpp \
    src/ModelFactory.cpp \
    src/NewGameDialog.cpp \
    src/RandomAlgorithm.cpp \
    src/Uttt.cpp \
    src/UtttMove.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    inc/GameUI.h \
    inc/AlgorithmInterface.h \
    inc/Fiar.h \
    inc/FiarMove.h \
    inc/GameInterface.h \
    inc/Human.h \
    inc/HumanAction.h \
    inc/IA.h \
    inc/MctsAlgorithm.h \
    inc/MinMaxAlgorithm.h \
    inc/ModelFactory.h \
    inc/MoveInterface.h \
    inc/PlayerInterface.h \
    inc/RandomAlgorithm.h \
    inc/Uttt.h \
    inc/UtttMove.h \
    inc/mainwindow.h \ \
    inc/GameController.h \
    inc/NewGameDialog.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
