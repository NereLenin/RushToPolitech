

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: mainScreenRectangle

    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    property int startHighlightPoint: 0
    property int endHighlightPoint: 0

    property string theoryText: "Обширный лекционный материал по этой теме невероятное количество тексто проверяем количество символов которые нужно здесь уместить чтобы было читаемо скока вот тут щас да хуй его знает но мы все пишим и пишим пишим и пишим и все и пиздец жизнь это что за шутка такая кто я чем я занят венец природы усажен в офисное кресло и подвергнут пыткам а все ради чего что это за симулякр жизни стали ли мы счастливей променяв пещеру из камня на пещеру из стекла и бетона мама помоги я так больше могу и еще смогу и так пока не сдохну"

    property string highlightedText: theoryText.substring(0,startHighlightPoint) + "<u><i>" + theoryText.substring(startHighlightPoint,endHighlightPoint) + "</u></i>" + theoryText.substring(endHighlightPoint,theoryText.length)

    property string outputText: endHighlightPoint > startHighlightPoint && endHighlightPoint < theoryText.length ? highlightedText : theoryText



    property string imageURL: "" // "qrc:/icons/questpic.jpg"
    property bool haveImage: imageURL !== ""

    property bool isImageUp: true


    Item {
        id: imageWithBorder
        visible: haveImage

        height: haveImage? (parent.height / 4) : 1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: isImageUp ? parent.top : none
        anchors.bottom: !isImageUp ? separatorLine.top : none
        anchors.margins: 20



        Rectangle {
            id: imageBorder
            anchors.fill: parent
            border.color: "#7A9DBF"
            opacity: 0.6
        }

        Image {
            id: image

            anchors.fill: imageBorder
            opacity: 1
            source: imageURL
            mirror: true
            fillMode: Image.PreserveAspectFit
        }
    }

    Text {
        id: textOfTheory
        text: outputText
        anchors.top: isImageUp ? imageWithBorder.bottom : parent.top
        anchors.bottom: isImageUp ? separatorLine.top : imageWithBorder.top

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 10

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 32
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap

        style: Text.Outline
        styleColor: "#383b39"
        color: "#383b39"
    }

    Rectangle {
        id: separatorLine
        anchors.left: prevButtonItem.left
        anchors.right: nextButtonItem.right
        anchors.bottom: nextButtonItem.top
        anchors.bottomMargin: 10

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }

    Item {
        id: prevButtonItem

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter

        anchors.margins: 15
        anchors.bottomMargin: 15
        anchors.rightMargin: 10

        height: (parent.height / 2) / 5

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
            text: "<"

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

    Item {
        id: nextButtonItem

        anchors.bottom: parent.bottom
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right

        anchors.margins: 15
        anchors.bottomMargin: 15
        anchors.leftMargin: 10

        height: (parent.height / 2) / 5

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
            text: ">"

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
}
