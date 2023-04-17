QT += quick

SOURCES += \
        appengine.cpp \
        exclamations.cpp \
        main.cpp \
        src/learnsession.cpp \
        src/mytimer.cpp \
        src/random.cpp \
        src/ticketbase.cpp \
        src/ticketinfo.cpp \
        src/tickets.cpp \
        src/ticketsdatabasereader.cpp \
        src/ticketsstatisticservice.cpp \
        src/ticketstatisticdatabasedriver.cpp

#resources.files = main.qml
#resources.prefix = /$${TARGET}
RESOURCES += \
    resources.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH +=

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/FailedLearnScreen.qml \
    qml/FinishExamFailed.qml \
    qml/FinishExamScreen.qml \
    qml/FinishLearnScreen.qml \
    qml/ItemOfDrawer.qml \
    qml/LSChooseVariant.qml \
    qml/LSInputValue.qml \
    qml/LearnTheory.qml \
    qml/LearnTheoryLastScreen.qml \
    qml/MyHeader.qml \
    qml/MyProgressBar.ui.qml \
    qml/Pager.qml \
    qml/RepeatScreen.qml \
    qml/SquareButton.ui.qml \
    qml/StartScreen.qml \
    qml/Ticket.ui.qml \
    qml/TicketsOfTopic.ui.qml \
    qml/Topic.ui.qml \
    qml/Topics.qml \
    qml/main.qml

SUBDIRS += \
    src/backAppTest.pro

HEADERS += \
    appengine.h \
    exclamations.h \
    src/learnsession.h \
    src/mytimer.h \
    src/random.h \
    src/ticketbase.h \
    src/ticketinfo.h \
    src/tickets.h \
    src/ticketsdatabasereader.h \
    src/ticketsstatisticservice.h \
    src/ticketstatisticdatabasedriver.h
