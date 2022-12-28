

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
        text: "Экзамен сдан без ошибок!\n" + "Добро пожаловать на УТС, страдай и наслаждайся"

        height: parent.height / 4

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
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Image {
        id: logoSurgu

        anchors.left: submitButtonItem.left
        anchors.right: submitButtonItem.right
        anchors.top: resultText.bottom
        anchors.bottom: submitButtonItem.top
        anchors.margins: 20

        source: "../../../../YandexDisk/RushPolytech/icons/logo.png"

        fillMode: Image.PreserveAspectFit
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
