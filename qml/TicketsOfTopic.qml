import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import TypeLearning 0.1

Rectangle {
    id: mainScreenRectangle

    objectName: "topicsTicketScreen"

    width: view.width
    height: view.height

    color: "#edecec"

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

            onClicked:{
                rootItem.startSession(LearnType.LearnTicketsInTopic)
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#cc0061c0"
            radius: 5
            opacity: 0.5
        }

        Text {
            text: "Прорешать"

            anchors.fill: parent
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
        id: listView
        anchors.left: submitButtonItem.left
        anchors.right: submitButtonItem.right
        anchors.top: parent.top
        anchors.bottom: submitButtonItem.top
        clip: true
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        model: topicsTicketModel

        delegate: Ticket {
            anchors.left: parent.left
            anchors.right: parent.right
            height: listView.height / 6

            canBeLearned: false
            ticketNumber: ticketIndex +1
            shortText: questionText

            onClicked: {
                rootItem.showSingleTicket(ticketIndex);
            }
        }
        currentIndex: 1

        //нада шоб при увеличении экрана отражалось больше текста
    }

    Rectangle {
        id: separatorLine

        anchors.left: listView.left
        anchors.right: listView.right
        anchors.bottom: listView.bottom

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }
}
