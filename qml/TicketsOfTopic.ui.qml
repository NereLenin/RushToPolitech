import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: mainScreenRectangle

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

        model: ListModel {
            ListElement {
                myTicketNumber: 69
                myShortText: "Фуууутбольчик мальчики походят на качков игра в ножечки плавно переходит на улицу чо сутулишся трапеция норм"
                myCanBeLearned: true
            }

            ListElement {
                myTicketNumber: 1238
                myShortText: "Привет, и ты проходишь мимо, я спрятала улыбку мне важно чтобы ты узнал секрет"
                myCanBeLearned: false
            }
            ListElement {
                myTicketNumber: 1187
                myShortText: "Фуууутбольчик мальчики походят на качков игра в ножечки плавно переходит на улицу чо сутулишся трапеция норм"
                myCanBeLearned: true
            }

            ListElement {
                myTicketNumber: 1987
                myShortText: "Я взял твою бу я ее ебу и мой глог или бля тт издаст туту здесь бля шутера и они не врут"
                myCanBeLearned: true
            }
            ListElement {
                myTicketNumber: 1941
                myShortText: "Фуууутбольчик мальчики походят на качков игра в ножечки плавно переходит на улицу чо сутулишся трапеция норм"
            }

            ListElement {
                myTicketNumber: 1488
                myShortText: "Главное степень искренности и я говорю тебе мысленное соси нам в этой близости не вырасти"
            }
            ListElement {
                myTicketNumber: 69
                myShortText: "Фуууутбольчик мальчики походят на качков игра в ножечки плавно переходит на улицу чо сутулишся трапеция норм"
            }

            ListElement {
                myTicketNumber: 1488
                myShortText: "Вот ты индеец я балдею бом бом спасибо ботяне за это прилажение черного света двадцатого века"
                myCanBeLearned: true
            }
        }
        delegate: Ticket {
            anchors.left: parent.left
            anchors.right: parent.right
            height: listView.height / 6
            canBeLearned: false
            ticketNumber: myTicketNumber
            shortText: myShortText
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
