QT += core gui
QT += widgets

SOURCES += \
    attributeeditor.cpp \
    classmaker_cpp.cpp \
    classviewer.cpp \
    functioneditor.cpp \
    main.cpp \
    methodeditor.cpp

HEADERS += \
    attributeeditor.h \
    classmaker_cpp.h \
    classviewer.h \
    functioneditor.h \
    methodeditor.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
