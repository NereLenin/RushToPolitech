

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {

    id: mainScreenRectangle
    objectName: "FailedLearnScreen"
    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    Keys.onPressed: (event)=> {
            if (event.key === Qt.Key_Enter ||
                event.key === Qt.Key_Space ||
                event.key === Qt.Key_Return)
                {
                submitItemButton.clicked()
                event.accepted = true;
                }
    }

    Item {
        id: submitButtonItem

        height: (parent.height / 2) / 4.2

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 20

        Button {
            id:submitItemButton
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true

            onClicked:
            {
                view.popToRegimeMainScreen();
                //view.popTo("StartScreen");
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#cc0061c0"
            radius: 5
            opacity: 0.5
        }

        Text {
            text: "Продолжить"

            anchors.fill: parent

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0

            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText
            font.pixelSize: 25

            styleColor: "#383b39"
        }
    }

    Item {
        id: learnFailedButtonItem

        height: (parent.height / 2) / 4.2

        anchors.bottom: submitButtonItem.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.bottomMargin: 15

        Button {
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true

            onClicked:
            {
                //myAppHeader.state = "WrongTicketsLearnSession";
                rootItem.startLearnFailedTicketsSession();
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#cc0061c0"
            radius: 5
            opacity: 0.5
        }

        Text {
            text: "Отработать ошибки"

            anchors.fill: parent

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0

            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText
            font.pixelSize: 25

            styleColor: "#383b39"
        }
    }

    ListView {
        id: listOfFailedTickets
        anchors.left: submitButtonItem.left
        anchors.right: submitButtonItem.right
        anchors.top: parent.top
        anchors.bottom: learnFailedButtonItem.top

        anchors.bottomMargin: 10
        anchors.topMargin: 10

        clip: true

        model: listWrongTickets

        delegate: Ticket {
            height: listOfFailedTickets.height / 5

            x: listOfFailedTickets.x
            width: listOfFailedTickets.width-15

            canBeLearned: true
            ticketNumber: ticketIndex
            shortText: questionText
        }
        currentIndex: 1
    }

    Rectangle {
        id: separatorLine

        anchors.left: listOfFailedTickets.left
        anchors.right: listOfFailedTickets.right
        anchors.bottom: listOfFailedTickets.bottom

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }

}
