QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lesson.cpp \
    lessonpassing.cpp \
    main.cpp \
    mainwindow.cpp \
    newdict.cpp \
    newword.cpp \
    results.cpp \
    wordeditform.cpp

HEADERS += \
    lesson.h \
    lessonpassing.h \
    mainwindow.h \
    newdict.h \
    newword.h \
    results.h \
    wordeditform.h

FORMS += \
    lesson.ui \
    lessonpassing.ui \
    mainwindow.ui \
    newdict.ui \
    newword.ui \
    results.ui \
    wordeditform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
