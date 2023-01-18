import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material


Rectangle {
    id: mainScreenRectangle

    //anchors.fill: parent
    width: view.width
    height: view.height

    color: "#edecec"

    property int chanceToPassExam: 10
    property int procOfAllLearned: 30
    property int procOfTodayLearned: 10

    Text {
        id: chanceToPassExamText
        text: "Вероятность сдачи экзамена : " + chanceToPassExam + "%"

        property int heightOfTextPerScreen: parent.height / 12

        height: heightOfTextPerScreen

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 5

        color: "#383b39"
        styleColor: "#383b39"
        style: Text.Outline

        font.family: "Courier new"
        font.styleName: "Полужирный"

        font.pixelSize: 25
        fontSizeMode: Text.Fit

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: personImage

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: chanceToPassExamText.bottom
        anchors.bottom: myProgressBar.top

        anchors.margins: 5

        source: "qrc:/icons/person.png"
        mirror: true

        fillMode: Image.PreserveAspectFit
    }

    MyProgressBar {
        id: myProgressBar

        property int heightOfProgressPerScreen: parent.height / 10

        height: heightOfProgressPerScreen

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: learnButton.top

        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 0
        anchors.topMargin: 5

        procOfProgress: procOfAllLearned
        procIncreasedProgress: procOfTodayLearned
    }

    Button {
        id: learnButton

        anchors.bottom: examButton.top
        anchors.left: parent.left
        anchors.margins: 20

        anchors.bottomMargin: 10

        width: examButton.width
        height: examButton.height

        font.pointSize: 14
        highlighted: false
        flat: false
        font.family: "Courier new"
        font.styleName: "Полужирный"
        font.capitalization: Font.AllLowercase
        font.bold: true
        autoExclusive: false

        Text {
            id: textLearn

            text: "Учить"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
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

        Image {
            id: learnIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            source: "qrc:/icons/learning.png"
            mirror: true
            fillMode: Image.PreserveAspectFit
        }


        onClicked:
        {

            /*

    property int indexOfCorrectVariant: 2

    property string textOfQuestion: "Это что за покемон неизвестная зверь тварь неясного сельского происхождения непонятной родословной???777"
    property string pathToImage: "qrc:/icons/questpic.jpg"

    property string variant4Text: "" //"Вариант 4"
    property string variant4PathToImg: ""//"qrc:/icons/questpic.jpg"

    property string variant3Text: "Вариант 3" //"Вариант 3"
    property string variant3PathToImg: "qrc:/icons/questpic.jpg" //"../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant2Text: "Секси" //"Вариант 4"
    property string variant2PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant1Text: "Жмых" //"Вариант 4"
    property string variant1PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"
            */
            /*
    property string correctAnswer: "жепич"
    property string textOfQuestion: "Это что за покемон неизвестная зверь тварь неясного сельского происхождения непонятной родословной???777"
    //property string pathToImage: ""
    property string pathToImage: "qrc:/icons/learning.png"
            */

            //-------------------отдать вот этот момент контроллеру?
            //

            view.push([ "qrc:/qml/FinishLearnScreen.qml", {"procOfAllLearned": "99"},

                       "qrc:/qml/LSChooseVariant.qml", {"variant1Text": "Чита",
                                                        "variant2Text": "Бирабиджан",
                                                        "variant3Text": "Там где нет Юли",
                                                        "variant4Text": "",
                                                        "textOfQuestion": "Худшее место на земле",
                                                        "indexOfCorrectVariant": "3"},
                       "qrc:/qml/LSInputValue.qml", {"textOfQuestion": "Сколько раз смотрели фильм с госленгом где он типа нацист? (введите число)",
                                                        "pathToImage": "qrc:/icons/questpic.jpg",
                                                        "correctAnswer": "1488"},
                       "qrc:/qml/LSChooseVariant.qml", {"variant1Text": "Пинус",
                                                        "variant2Text": "Повербанк в виде палки",
                                                        "variant3Text": "Палка с водой заряженой",
                                                        "variant4Text": "Палка которую поставили на ставку (зарядили)",
                                                        "textOfQuestion": "ЗАГАДКА ЕБАТЬ\nПалка заряжена не стреляет",
                                                        "indexOfCorrectVariant": "1"}

                        ]);
        }
    }

    Button {
        id: examButton

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
            id: examText
            text: "Сдать"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
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

        Image {
            id: examIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "qrc:/icons/exam.png"
            mirror: true
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

    Button {
        id: repeatButton

        anchors.bottom: theoryButton.top
        anchors.right: parent.right
        anchors.margins: 20

        anchors.bottomMargin: 10
        width: examButton.width
        height: examButton.height

        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: repeatText
            text: "Повтор"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
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

        Image {
            id: repeatIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 20
            anchors.topMargin: 30
            anchors.bottomMargin: 30

            //anchors.bottom: myProgressBar.top //поменять на наш компонент
            //anchors.margins: 5
            source: "qrc:/icons/repeat.png"
            mirror: true
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

    Button {
        id: theoryButton

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        anchors.bottomMargin: 10
        width: examButton.width
        height: examButton.height

        font.pointSize: 16
        flat: false
        highlighted: false
        font.family: "Courier new"
        autoExclusive: false
        font.capitalization: Font.AllLowercase
        font.styleName: "Полужирный"
        font.bold: true

        Text {
            id: theoryText
            text: "Теория"

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.pixelSize: 25

            anchors.left: parent.horizontalCenter
            horizontalAlignment: Text.AlignLeft
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

        Image {
            id: theoryIcon

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            anchors.margins: 5
            anchors.rightMargin: 10
            anchors.topMargin: 20
            anchors.bottomMargin: 20

            source: "qrc:/icons/theory.png"
            mirror: true
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
}
