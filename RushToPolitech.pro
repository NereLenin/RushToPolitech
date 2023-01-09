QT += quick

SOURCES += \
        main.cpp

#resources.files = main.qml
#resources.prefix = /$${TARGET}
RESOURCES += qml_resources.qrc#resources \


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH +=

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/FailedLearnScreen.ui.qml \
    qml/FinishExamFailed.ui.qml \
    qml/FinishExamSuccess.ui.qml \
    qml/FinishLearnScreen.ui.qml \
    qml/ItemOfDrawer.qml \
    qml/LSChooseVariant.ui.qml \
    qml/LSInputValue.ui.qml \
    qml/LearnTheory.ui.qml \
    qml/LearnTheoryLastScreen.ui.qml \
    qml/MyHeader.qml \
    qml/MyProgressBar.ui.qml \
    qml/RepeatScreen.ui.qml \
    qml/SquareButton.ui.qml \
    qml/StartScreen.ui.qml \
    qml/Ticket.ui.qml \
    qml/TicketsOfTopic.ui.qml \
    qml/Topic.ui.qml \
    qml/Topics.ui.qml \
    qml/main.qml \
