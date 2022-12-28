//LS - Learn Screen


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

    property string textOfQuestion: "Это что за покемон неизвестная зверь тварь неясного сельского происхождения непонятной родословной???777"
    //property string pathToImage: ""
    property string pathToImage: "../../../../YandexDisk/RushPolytech/icons/learning.png"

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
            text: "Ответить"

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

    Rectangle {
        id: separatorLine
        anchors.left: inputTextRectangle.left
        anchors.right: inputTextRectangle.right
        anchors.bottom: inputTextRectangle.top
        anchors.bottomMargin: 10

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }

    Text {
        id: fullTextOfQuestion
        text: textOfQuestion

        //height: (parent.height / 2) / 1.5
        anchors.top: imageWithBorder.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: separatorLine.bottom
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap

        font.family: "Courier new"
        font.pixelSize: 37
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Item {
        id: imageWithBorder
        height: pathToImage == "" ? 1 : parent.height / 3

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 5
        anchors.topMargin: 10
        visible: pathToImage == "" ? false : true

        Rectangle {
            id: imageBorder
            anchors.fill: parent
            border.color: "#7A9DBF"
            opacity: 0.6
        }

        Image {
            id: image
            anchors.fill: imageBorder
            anchors.margins: 10
            opacity: 1
            source: pathToImage

            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: inputTextRectangle
        height: submitButtonItem.height

        anchors.left: submitButtonItem.left
        anchors.right: submitButtonItem.right
        anchors.bottom: submitButtonItem.top
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        TextField {
            id: myTextField
            color: "#383b39"

            anchors.fill: parent

            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            activeFocusOnTab: true
            focus: true
            hoverEnabled: true
            font.styleName: "Полужирный"
            font.family: "Courier New"

            placeholderTextColor: "#383b39"
            selectedTextColor: "#7A9DBF"

            Text {
                anchors.fill: parent
                text: "Введите ответ..."
                color: "#383B39"
                font.pixelSize: 25
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Полужирный"
                font.family: "Courier New"
                visible: !parent.text
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

