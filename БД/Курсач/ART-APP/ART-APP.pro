QT += core gui sql printsupport widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    faculties.cpp \
    globals.cpp \
    housings.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    marks.cpp \
    menuwindow.cpp \
    schedules.cpp \
    students.cpp \
    subjects.cpp \
    teachers.cpp

HEADERS += \
    faculties.h \
    globals.h \
    housings.h \
    loginwindow.h \
    mainwindow.h \
    marks.h \
    menuwindow.h \
    schedules.h \
    students.h \
    subjects.h \
    teachers.h

FORMS += \
    faculties.ui \
    housings.ui \
    loginwindow.ui \
    mainwindow.ui \
    marks.ui \
    menuwindow.ui \
    schedules.ui \
    students.ui \
    subjects.ui \
    teachers.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
