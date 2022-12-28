

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: rootHeaderItem
    height: 80
    width: 500

    property bool showRightButton: true
    property int burgerLineHeight: 6
    property string headerText: "УТС"
    property string pathToRightIconButton: "../../../RushToPolitech/icons/studyIcon.png"
    property string headerTime: "19:23"

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        color: "#D9D9D9"
    }

    Item {
        id: burgerButtonItem

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: height

        Button {
            id: burgerButton
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true
            flat: true
        }

        Rectangle {
            anchors.fill: parent
            color: "#ccBBBBBB"
            radius: 5
            opacity: 0.5
        }

        Item {
            id: myBurger
            height: parent.height / 2
            width: height / 0.8
            anchors.centerIn: parent
            anchors.margins: 5

            Rectangle {
                id: topLine
                anchors.top: parent.top
                height: burgerLineHeight
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#7A9DBF"
            }
            Rectangle {
                id: middleLine
                anchors.verticalCenter: parent.verticalCenter
                height: burgerLineHeight
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#7A9DBF"
            }
            Rectangle {
                id: bottomLine
                anchors.bottom: parent.bottom
                height: burgerLineHeight
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#7A9DBF"
            }
        }
    }

    Item {
        id: rightButtonItem
        visible: showRightButton

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: height

        Button {
            id: rightButton
            anchors.fill: parent

            font.family: "Courier new"
            font.pointSize: 14
            font.styleName: "Полужирный"
            font.bold: true
            flat: true
        }

        Rectangle {
            anchors.fill: parent
            color: "#ccBBBBBB"
            radius: 5
            opacity: 0.5
        }

        Image {
            id: rightButtonIcon
            anchors.fill: parent
            anchors.margins: 10
            source: pathToRightIconButton
        }
    }

    Text {
        id: chanceToPassExamText
        text: headerText
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.left: burgerButtonItem.right
        anchors.right: rightButtonItem.left

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        color: "#383b39"
        styleColor: "#383b39"
        style: Text.Outline

        font.family: "Courier new"
        font.styleName: "Полужирный"

        font.pixelSize: 52
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: timeText
        visible: (headerTime != "") && (!showRightButton)

        text: headerTime

        width: parent.width / 3

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        anchors.leftMargin: 5
        anchors.rightMargin: 10
        padding: 5

        color: "#383b39"
        styleColor: "#383b39"
        style: Text.Outline

        font.family: "Courier new"
        font.styleName: "Полужирный"

        font.pixelSize: 48
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    states: [
        State {
            name: "MainScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
            }
        },
        State {
            name: "LearnScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Учим"
            }
        },
        State {
            name: "ResultScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Результат"
            }
        },
        State {
            name: "WrongTicketsScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Ошибки"
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

