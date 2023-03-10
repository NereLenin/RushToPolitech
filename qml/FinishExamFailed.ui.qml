

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

    Text {
        id: resultText
        text: "Экзамен сдан с ошибками...\n" + "Придется идти работать в макдональдс\n"

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

        source: "../../../../YandexDisk/RushPolytech/icons/logo.png"

        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: statisticText
        text: "Правильно: 5 Ошибок : 3 \nЗатрачено времени: 08:59"

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

            source: "../../../../YandexDisk/RushPolytech/icons/bilets.png"

            fillMode: Image.PreserveAspectFit
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
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true
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
