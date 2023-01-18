

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
    property bool subtopic: false

    property string nameTopic: "Программирование"
    property string pathTopicIcon: "qrc:/icons/theory.png"

    height: 150
    width: 500

    Text {
        id: text2
        text: nameTopic
        color: "#383b39"

        anchors.top: parent.top
        width: parent.width * 0.7

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10

        elide: Text.ElideNone

        font.pixelSize: 28
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        //wrapMode: Text.WordWrap
        //anchors.topMargin: 6
        maximumLineCount: 10
        minimumPixelSize: 6
        style: Text.Outline
        scale: 1
        font.styleName: "Полужирный"
        padding: 5
        fontSizeMode: Text.Fit
        font.family: "Courier new"
        textFormat: Text.PlainText
        styleColor: "#383b39"
    }

    Button {
        id: repeatButton

        visible: subtopic

        width: height
        height: parent.height / 1.5

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Image {
            id: repeatIcon

            anchors.fill: parent
            anchors.margins: 15

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "qrc:/icons/bilets.png"
            //mirror: true
            fillMode: Image.PreserveAspectFit
            //debag border


            /*
            Rectangle {anchors.fill: parent
                color: "#00FFFFFF"
                border.width: 2
                border.color: red
            }
            */
        }
    }

    Image {
        id: topicIcon
        x: 366
        width: 119

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: text2.right
        visible: !subtopic

        //anchors.
        anchors.margins: 15

        //anchors.bottom: myProgressBar.top //поменять на наш компонент
        //anchors.margins: 5
        source: pathTopicIcon
        //mirror: true
        fillMode: Image.PreserveAspectFit
        //debag border


        /*
        Rectangle {anchors.fill: parent
            color: "#00FFFFFF"
            border.width: 2
            border.color: red
        }
        */
    }

    //separate
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
    D{i:0;formeditorZoom:0.9}
}
##^##*/

