

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: rootItem

    height: 150
    width: 500

    property int ticketNumber: 22
    property string shortText: "Есть значит два стула на одном пики точеные на другом хуи дроченные на какой сам сядешь на какой жепу посадишь "
    property bool canBeLearned: false

    property int shortTextCutSize: canBeLearned ? 50 : 80

    Text {
        id: ticketNumberText
        text: "Вопрос №" + ticketNumber

        height: parent.height / 3
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignBottom

        font.family: "Courier new"
        font.pixelSize: 30
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Text {
        id: textOfQuestion
        text: shortText.length > shortTextCutSize ? shortText.substring(
                                                        0,
                                                        shortTextCutSize) + "..." : shortText

        anchors.top: ticketNumberText.bottom
        anchors.right: canBeLearned ? watchRightAnswerButton.left : parent.right

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop

        font.family: "Courier new"
        font.pixelSize: 25
        maximumLineCount: 10
        minimumPixelSize: 6
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Button {
        id: watchRightAnswerButton
        visible: canBeLearned

        width: height
        height: parent.height / 1.5

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5

        Image {
            id: repeatIcon

            anchors.fill: parent
            anchors.margins: 15
            source: "../../../../YandexDisk/RushPolytech/icons/theory.png"

            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: separatorLine

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/

