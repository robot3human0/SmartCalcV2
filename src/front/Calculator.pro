QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/model.cc \
    controller.cc \
    graph.cc \
    main.cc \
    mylineedit.cc \
    qcustomplot.cc

HEADERS += \
    ../model/model.h \
    controller.h \
    graph.h \
    mylineedit.h \
    qcustomplot.h

FORMS += \
    controller.ui \
    graph.ui

ICON = img/icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
