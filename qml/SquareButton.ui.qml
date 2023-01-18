import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 200
    height: 200

    property string textOfButton: "Сдать"
    property string pathToIcon: "qrc:/icons/exam.png"

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
