

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import RushPoliTech

Rectangle {
    id: mainScreenRectangle

    width: 420
    height: 736
    anchors.fill: parent
    color: "#edecec"

    property int chanceToPassExam: 10
    property int procOfAllLearned: 30
    property int procOfTodayLearned: 10

    Text {
        id: chanceToPassExamText
        text: "Вероятность сдачи экзамена : " + chanceToPassExam + "%"

        property int heightOfTextPerScreen: parent.height / 12

        height: heightOfTextPerScreen

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        color: "#383b39"
        styleColor: "#383b39"
        style: Text.Outline

        font.family: "Courier new"
        font.styleName: "Полужирный"

        font.pixelSize: 25
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: personImage

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: chanceToPassExamText.bottom
        anchors.bottom: myProgressBar.top

        anchors.margins: 5

        source: "../../../../YandexDisk/RushPolytech/icons/person.png"
        mirror: true

        fillMode: Image.PreserveAspectFit
    }

    MyProgressBar {
        id: myProgressBar

        property int heightOfProgressPerScreen: parent.height / 10

        height: heightOfProgressPerScreen

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: learnButton.top

        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 0
        anchors.topMargin: 5

        procOfProgress: procOfAllLearned
        procIncreasedProgress: procOfTodayLearned
    }

    Button {
        id: learnButton

        anchors.bottom: examButton.top
        anchors.left: parent.left
        anchors.margins: 20

        anchors.bottomMargin: 10

        width: examButton.width
        height: examButton.height

        font.pointSize: 14
        highlighted: false
        flat: false
        font.family: "Courier new"
        font.styleName: "Полужирный"
        font.capitalization: Font.AllLowercase
        font.bold: true
        autoExclusive: false

        Text {
            id: textLearn

            text: "Учить"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        Image {
            id: learnIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            source: "../../../../YandexDisk/RushPolytech/icons/learning.png"
            mirror: true
            fillMode: Image.PreserveAspectFit
        }
    }

    Button {
        id: examButton

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 20
        anchors.bottomMargin: 10

        width: (parent.width / 2) - 35
        height: parent.height / 5

        layer.wrapMode: ShaderEffectSource.Repeat
        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true
        Text {
            id: examText
            text: "Сдать"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        Image {
            id: examIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "../../../../YandexDisk/RushPolytech/icons/exam.png"
            mirror: true
            fillMode: Image.PreserveAspectFit
            //debag border


            /*
            Rectangle {anchors.fill: parent
                color: "#00FFFFFF"
                border.width: 2
                border.color: red
            }
            */
        }
    }

    Button {
        id: repeatButton

        anchors.bottom: theoryButton.top
        anchors.right: parent.right
        anchors.margins: 20

        anchors.bottomMargin: 10
        width: examButton.width
        height: examButton.height

        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: repeatText
            text: "Повтор"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        Image {
            id: repeatIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 20
            anchors.topMargin: 30
            anchors.bottomMargin: 30

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "../../../../YandexDisk/RushPolytech/icons/repeat.png"
            mirror: true
            fillMode: Image.PreserveAspectFit
            //debag border


            /*
            Rectangle {anchors.fill: parent
                color: "#00FFFFFF"
                border.width: 2
                border.color: red
            }
            */
        }
    }

    Button {
        id: theoryButton

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        anchors.bottomMargin: 10
        width: examButton.width
        height: examButton.height

        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: theoryText
            text: "Теория"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        Image {
            id: theoryIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "../../../../YandexDisk/RushPolytech/icons/theory.png"
            mirror: true
            fillMode: Image.PreserveAspectFit
            //debag border


            /*
            Rectangle {anchors.fill: parent
                color: "#00FFFFFF"
                border.width: 2
                border.color: red
            }
            */
        }
    }
}
