QT       += \
    core gui \
    gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \ c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/Autocomplete.cpp \
    Sources/GuideWidget.cpp \
    Sources/Controller.cpp \
    Sources/ImageWidget.cpp \
    Sources/TextFieldWidget.cpp \
    Sources/TileGroupWidget.cpp \
    Sources/TileWidget.cpp \
    Sources/Trie.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp

HEADERS += \
    Headers/GP4k_ButtonsMapping.h \
    Headers/Autocomplete.h \
    Headers/Controller.h \
    Headers/GP4k_GuiMapping.h \
    Headers/GP4k_TilesMapping.h \
    Headers/GP4k_Typedefs.h \
    Headers/GuideWidget.h \
    Headers/ImageWidget.h \
    Headers/TextFieldWidget.h \
    Headers/TileGroupWidget.h \
    Headers/TileWidget.h \
    Headers/Trie.h \
    Headers/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
