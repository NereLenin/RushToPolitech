

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
    objectName: "finishLearningScreen"
    id: mainScreenRectangle

    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    property string mainText: appEngine.finishScreenText
    property int chanceToPassExam: appEngine.chanceToPassExam
    property int todayBustToChancePassExam: 0

    property int procOfAllLearned: appEngine.procOfAllLearned
    property int procOfTodayLearned: appEngine.procOfTodayLearned

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

        height: parent.height / 8

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

    Text {
        id: chancePassExamText
        text: "Вероятность сдачи экзамена: " + chanceToPassExam
              + (todayBustToChancePassExam > 0 ? '+' + todayBustToChancePassExam : '') + "%"

        height: parent.height / 14

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: resultText.bottom
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

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Image {
        id: image
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: chancePassExamText.bottom
        anchors.bottom: myProgressBar.top //поменять на наш компонент
        anchors.margins: 5
        source: "qrc:/icons/person.png"
        mirror: true
        fillMode: Image.PreserveAspectFit
    }

    MyProgressBar {
        id: myProgressBar
        height: parent.height / 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: failedText.top
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 0
        anchors.topMargin: 5

        procOfProgress: procOfAllLearned
        procIncreasedProgress: procOfTodayLearned
    }

    Text {

        id: failedText
        text: "Правильно: " + countRightAnswer +
              " Ошибок : " + countWrongAnswer +
              " \nЗатрачено времени: " + timeLasting

        height: (parent.height / 2) / 4.2
        width: submitButtonItem.width * 0.75

        anchors.left: submitButtonItem.left
        anchors.bottom: submitButtonItem.top
        anchors.topMargin: 5
        anchors.rightMargin: 5
        padding: 5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 25
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit
        lineHeight: 1.5

        style: Text.Outline
        styleColor: "#383b39"
        color: "#383b39"
    }

    Button {
        id: watchFailedTicketsButton

        anchors.bottom: failedText.bottom
        anchors.right: submitButtonItem.right
        anchors.left: failedText.right
        anchors.top: failedText.top
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
                view.push("FailedLearnScreen.qml");
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
                //view.push("qrc:/qml/StartScreen.qml");
                myAppHeader.state = "StartScreen"
                view.popTo("StartScreen");
                //view.pop(StartScreen)
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
