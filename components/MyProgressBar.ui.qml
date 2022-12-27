

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
    height: 80
    width: 500

    property int procOfProgress: 55
    property int procIncreasedProgress: 0

    Rectangle {
        id: backgroundProgress

        height: rootItem.height / 2
        anchors.top: rootItem.top
        anchors.left: rootItem.left
        anchors.right: rootItem.right
        color: "#D9D9D9"
    }

    Rectangle {
        id: currentProgress

        height: parent.height / 2
        width: ((parent.width) / 100) * procOfProgress

        anchors.top: parent.top
        anchors.left: parent.left

        color: "#7A9DBF"

        Rectangle {
            id: buffedProgress
            width: ((parent.width) / 100) * procIncreasedProgress

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            color: "#7A81BF"
        }
    }

    Text {
        id: learnedText
        text: "Выучено " + (procIncreasedProgress
                            > 0 ? (procOfProgress - procIncreasedProgress) + "+"
                                  + procIncreasedProgress : procOfProgress) + "%"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: backgroundProgress.bottom
        anchors.bottom: parent.bottom
        padding: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.styleName: "Полужирный"
        font.pixelSize: 25
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }
}
