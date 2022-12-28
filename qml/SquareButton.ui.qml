

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 200
    height: 200

    property string textOfButton: "Сдать"
    property string pathToIcon: "../../../../YandexDisk/RushPolytech/icons/exam.png"

    Button {
        id: squareButton

        anchors.fill: parent

        font.family: "Courier new"
        font.styleName: "Полужирный"

        Text {
            id: buttonLabel
            text: textOfButton

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.horizontalCenter

            anchors.rightMargin: 5
            anchors.topMargin: 0
            padding: 5

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            font.family: "Courier new"
            font.pixelSize: 25
            font.styleName: "Полужирный"
            style: Text.Outline

            fontSizeMode: Text.Fit

            color: "#383b39"
            styleColor: color
        }

        Image {
            id: buttonIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            source: pathToIcon

            fillMode: Image.PreserveAspectFit
        }
    }
}
