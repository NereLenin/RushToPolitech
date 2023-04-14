import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: mainRectangle

    width: view.width
    height: view.height
    objectName: "RepeatScreen"

    Component.onCompleted: {
        myAppHeader.state = "RepeatScreen";
    }

    color: "#edecec"

    property int ticketsCount: appEngine.allTicketsCount
    property int learnedTicketsCount: appEngine.learnedTicketsCount
    property int hardTicketsCount: appEngine.hardTicketsCount
    property int forgottenTicketsCount: appEngine.forgottenTicketsCount

    property int chanceToPassExam: appEngine.chanceToPassExam
    property int procOfAllLearned: appEngine.procOfAllLearned
    property int procOfTodayLearned: appEngine.procOfTodayLearned

    property int statisiticsTextHeight: view.height / 12

    Text {
        id: allTicketsText
        text: "Всего вопросов: " + ticketsCount

        height: statisiticsTextHeight

        anchors.left: parent.left
        anchors.right: personImage.horizontalCenter
        anchors.top: parent.top

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        font.family: "Courier new"
        font.pixelSize: 25
        fontSizeMode: Text.Fit
        font.styleName: "Полужирный"

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        style: Text.Outline
        styleColor: "#383b39"
        color: "#383b39"
    }

    Text {
        id: learnedText
        text: "Выученных: " + learnedTicketsCount

        height: statisiticsTextHeight

        anchors.left: parent.left
        anchors.right: personImage.horizontalCenter
        anchors.top: allTicketsText.bottom

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        font.family: "Courier new"
        font.pixelSize: 25
        fontSizeMode: Text.Fit
        font.styleName: "Полужирный"

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        style: Text.Outline
        styleColor: "#383b39"
        color: "#383b39"
    }

    Text {
        id: troubleText
        text: "Проблемных: " + hardTicketsCount

        height: statisiticsTextHeight

        anchors.left: parent.left
        anchors.right: personImage.horizontalCenter
        anchors.top: learnedText.bottom

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 25
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Text {
        id: forgotenText
        text: "Забытых: " + forgottenTicketsCount

        height: statisiticsTextHeight

        anchors.left: parent.left
        anchors.right: personImage.horizontalCenter
        anchors.top: troubleText.bottom

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.topMargin: 0
        padding: 5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 25
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Text {
        id: examChanceText
        text: "Вероятность сдачи экзамена : " + chanceToPassExam + "%"

        height: statisiticsTextHeight

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: myProgressBar.top

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        font.family: "Courier new"
        font.pixelSize: 25
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        style: Text.Outline
        color: "#383b39"
        styleColor: "#383b39"
    }

    Image {
        id: personImage

        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: allTicketsText.bottom
        anchors.bottom: examChanceText.top //поменять на наш компонент

        anchors.margins: 5

        source: "qrc:/icons/person.png"
        mirror: true

        fillMode: Image.PreserveAspectFit
    }

    MyProgressBar {
        id: myProgressBar

        height: parent.height / 10

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: problemButton.top

        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 0
        anchors.topMargin: 5

        procOfProgress: procOfAllLearned
        procIncreasedProgress: procOfTodayLearned
    }

    Button {
        id: problemButton

        anchors.bottom: repeatRandomTen.top
        anchors.left: parent.left
        anchors.margins: 20

        anchors.bottomMargin: 10

        width: repeatRandomTen.width
        height: repeatRandomTen.height

        font.pointSize: 14
        highlighted: false
        flat: false
        font.family: "Courier new"
        font.styleName: "Полужирный"
        font.capitalization: Font.AllLowercase
        font.bold: true
        autoExclusive: false

        Text {
            id: problemText

            text: "Повторить\nпроблемные"

            anchors.fill: parent
            font.pixelSize: 25

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        onClicked: {
            myAppHeader.state = "RepeatSession";
            rootItem.startRepeatHardSession();
        }
    }

    Button {
        id: repeatRandomTen

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 20
        anchors.bottomMargin: 10

        width: (parent.width / 2) - 35
        height: parent.height / 5

        layer.wrapMode: ShaderEffectSource.Repeat
        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: randomTenText
            text: "Повторить 10\nслучайных"

            anchors.fill: parent
            font.pixelSize: 25

            horizontalAlignment: Text.AlignHCenter

            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        onClicked: {
            myAppHeader.state = "RepeatSession";
            rootItem.startRepeatRandomSession();
        }
    }

    Button {
        id: repeatTimeButton

        anchors.bottom: forgottenButton.top
        anchors.right: parent.right
        anchors.margins: 20

        anchors.bottomMargin: 10
        width: repeatRandomTen.width
        height: repeatRandomTen.height

        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: repeatTimeText
            text: "Повтор на\nвремя"

            anchors.fill: parent
            font.pixelSize: 25

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }
        onClicked: {
            myAppHeader.state = "RepeatWithTimerSession";
            rootItem.startRepeatWithTimerSession();
        }
    }

    Button {
        id: forgottenButton
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        anchors.bottomMargin: 10
        width: repeatRandomTen.width
        height: repeatRandomTen.height

        //text: qsTr("")
        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: forgottenText
            text: "Повторить\nзабытые"

            anchors.fill: parent
            font.pixelSize: 25

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            style: Text.Outline
            scale: 1

            anchors.rightMargin: 5
            anchors.topMargin: 0
            font.styleName: "Полужирный"
            padding: 5
            fontSizeMode: Text.Fit
            font.family: "Courier new"
            textFormat: Text.PlainText

            styleColor: "#383b39"
        }

        onClicked: {
            myAppHeader.state = "RepeatSession";
            rootItem.startRepeatForgottenSession();
        }
    }
}
