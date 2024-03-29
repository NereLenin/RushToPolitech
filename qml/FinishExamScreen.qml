

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import TypeLearning 0.1
Rectangle {
    id: mainScreenRectangle
    objectName: "finishExamScreen"
    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    property string mainText: appEngine.finishScreenText
    property int countRightAnswer : appEngine.countRightAnswer
    property int countWrongAnswer : appEngine.countWrongAnswer
    property string timeLasting: appEngine.sessionLasting

    Keys.onPressed: (event)=> {
            if (event.key === Qt.Key_Enter ||
                event.key === Qt.Key_Space ||
                event.key === Qt.Key_Return)
                {
                submitItemButton.clicked()
                event.accepted = true;
                }
    }

    Text {
        id: resultText
        text: mainText

        height: parent.height / 6

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 42
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        wrapMode: Text.WordWrap

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Image {
        id: surguLogo

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: resultText.bottom
        anchors.bottom: statisticText.top

        anchors.margins: 5

        source: "qrc:/icons/logo.png"

        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: statisticText
        text: "Правильно: " + countRightAnswer + " Ошибок : " + countWrongAnswer +" \nЗатрачено времени: " + timeLasting

        height: (parent.height / 2) / 4.2
        width: submitButtonItem.width * 0.75

        anchors.left: submitButtonItem.left
        anchors.bottom: againButtonItem.top
        anchors.topMargin: 5
        anchors.rightMargin: 5
        padding: 5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        lineHeight: 1.5

        font.family: "Courier new"
        font.pixelSize: 25
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Button {
        id: watchFailedTicketsButton

        anchors.bottom: statisticText.bottom
        anchors.right: submitButtonItem.right
        anchors.left: statisticText.right
        anchors.top: statisticText.top

        anchors.bottomMargin: 5

        Image {
            anchors.fill: parent
            anchors.margins: 15

            source: "qrc:/icons/bilets.png"

            fillMode: Image.PreserveAspectFit
        }
        onClicked:
        {
            if(countWrongAnswer > 0)
                rootItem.navigateTo("FailedLearnScreen");
        }
    }

    Item {
        id: againButtonItem

        height: (parent.height / 2) / 4.2

        anchors.bottom: submitButtonItem.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 10

        Button {
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true

            onClicked: {
              rootItem.startSession(LearnType.Exam);
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#cc0061c0"
            radius: 5
            opacity: 0.5
        }

        Text {
            text: "Еще раз"

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
                rootItem.returnToRegimeMainPage();
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
}
