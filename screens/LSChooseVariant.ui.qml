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
    property string pathToImage: "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant4Text: "Вариант4" //"Вариант 4"
    property string variant4PathToImg: "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant3Text: "" //"Вариант 4"
    property string variant3PathToImg: "" //"../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant2Text: "Вариант 2" //"Вариант 4"
    property string variant2PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant1Text: "Вариант 1" //"Вариант 4"
    property string variant1PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property int buttonSize: height / 2 / 4.2

    Item {
        id: imageWithBorder
        height: pathToImage == "" ? 1 : parent.height / 4

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
            anchors.fill: imageBorder
            anchors.margins: 10
            opacity: 1
            source: pathToImage

            fillMode: Image.PreserveAspectFit
        }
    }

    Text {
        id: fullTextOfQuestion
        text: textOfQuestion

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

    Rectangle {
        id: separatorLine
        anchors.left: variant1Button.left
        anchors.right: variant1Button.right
        anchors.bottom: variant1Button.top
        anchors.bottomMargin: 3

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }

    Button {
        id: variant4Button

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 10

        height: variant4Text != "" || variant4PathToImg != "" ? buttonSize : 1
        visible: variant4Text != "" || variant4PathToImg != ""

        Text {
            text: variant4PathToImg == "" ? variant4Text : ""
            anchors.fill: parent
            padding: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
            style: Text.Outline

            font.family: "Courier new"
            font.pixelSize: 25
            font.styleName: "Полужирный"

            fontSizeMode: Text.Fit

            color: "#383b39"
            styleColor: "#383b39"
        }

        Item {
            id: var4ButtonImage
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            visible: variant4PathToImg != ""

            Rectangle {
                id: btn4ImgBorder
                anchors.fill: parent
                border.color: "#7A9DBF"
                opacity: 0.6
            }

            Image {
                anchors.fill: btn4ImgBorder
                anchors.margins: 2
                opacity: 1
                source: variant4PathToImg

                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Button {

        id: variant3Button

        anchors.bottom: variant4Button.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 5

        height: variant3Text != "" || variant3PathToImg != "" ? buttonSize : 1
        visible: variant3Text != "" || variant3PathToImg != ""

        Text {
            text: variant3PathToImg == "" ? variant3Text : ""
            anchors.fill: parent
            padding: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
            style: Text.Outline

            font.family: "Courier new"
            font.pixelSize: 25
            font.styleName: "Полужирный"

            fontSizeMode: Text.Fit

            color: "#383b39"
            styleColor: "#383b39"
        }

        Item {
            id: var3ButtonImage
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            visible: variant3PathToImg != ""

            Rectangle {
                id: btn3ImgBorder
                anchors.fill: parent
                border.color: "#7A9DBF"
                opacity: 0.6
            }

            Image {
                anchors.fill: btn3ImgBorder
                anchors.margins: 2
                opacity: 1
                source: variant3PathToImg

                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Button {

        id: variant2Button

        anchors.bottom: variant3Button.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 5

        height: variant2Text != "" || variant2PathToImg != "" ? buttonSize : 1
        visible: variant2Text != "" || variant2PathToImg != ""

        Text {
            text: (variant2PathToImg == "") ? variant2Text : ""
            anchors.fill: parent
            padding: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
            style: Text.Outline

            font.family: "Courier new"
            font.pixelSize: 25
            font.styleName: "Полужирный"

            fontSizeMode: Text.Fit

            color: "#383b39"
            styleColor: "#383b39"
        }

        Item {
            id: var2ButtonImage
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            visible: variant2PathToImg != ""
            Rectangle {
                id: btn2ImgBorder
                anchors.fill: parent
                border.color: "#7A9DBF"
                opacity: 0.6
            }

            Image {
                anchors.fill: btn2ImgBorder
                anchors.margins: 2
                opacity: 1
                source: variant2PathToImg

                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Button {

        id: variant1Button

        anchors.bottom: variant2Button.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 5

        height: variant1Text != "" || variant1PathToImg != "" ? buttonSize : 1
        visible: variant1Text != "" || variant1PathToImg != ""

        Text {
            text: variant1PathToImg == "" ? variant1Text : ""
            anchors.fill: parent
            padding: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
            style: Text.Outline

            font.family: "Courier new"
            font.pixelSize: 25
            font.styleName: "Полужирный"

            fontSizeMode: Text.Fit

            color: "#383b39"
            styleColor: "#383b39"
        }

        Item {
            id: var1ButtonImage
            width: parent.width / 2
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            visible: variant1PathToImg != ""

            Rectangle {
                id: btn1ImgBorder
                anchors.fill: parent
                border.color: "#7A9DBF"
                opacity: 0.6
            }

            Image {
                anchors.fill: btn1ImgBorder
                anchors.margins: 2
                opacity: 1
                source: variant1PathToImg

                fillMode: Image.PreserveAspectFit
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

