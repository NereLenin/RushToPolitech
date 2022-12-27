QT += quick

SOURCES += \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    components/MyProgressBar.ui.qml \
    components/SquareButton.ui.qml \
    components/Ticket.ui.qml \
    components/Topic.ui.qml \
    screens/FailedLearnScreen.ui.qml \
    screens/FinishExamFailed.ui.qml \
    screens/FinishExamSuccess.ui.qml \
    screens/FinishLearnScreen.ui.qml \
    screens/LSChooseVariant.ui.qml \
    screens/LSInputValue.ui.qml \
    screens/LearnTheory.ui.qml \
    screens/LearnTheoryLastScreen.ui.qml \
    screens/RepeatScreen.ui.qml \
    screens/StartScreen.ui.qml \
    screens/TicketsOfTopic.ui.qml \
    screens/Topics.ui.qml
