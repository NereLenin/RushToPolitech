

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material

Item {
    id: rootItem
    height: 50
    width: 100

    property string textOfItem: "Текст боковой панели"

    signal clicked()

    Button {
        id: itemButton
        anchors.fill: parent
        anchors.leftMargin: 3
        anchors.rightMargin: 3
        flat: true

        onClicked: rootItem.clicked()
    }

    Rectangle {
        anchors.fill: parent
        color: "#ccBBBBBB"
        opacity: 0.5
    }

    Text {
        id: itemText
        text: textOfItem
        anchors.fill: parent

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        color: "#383b39"
        styleColor: "#383b39"
        style: Text.Outline

        font.family: "Courier new"
        font.styleName: "Полужирный"

        font.pixelSize: 18
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: separatorLine

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        height: 1

        color: "#7A9DBF"
        opacity: 0.4
    }
}
/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

