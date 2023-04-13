//LS - Learn Screen
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material


Rectangle {
    id: mainScreenRectangle

    width: view.width
    height: view.height

    color: "#edecec"

    property int ticketIndex: 0
    property int indexOfCorrectVariant: 2
    //property int indexOfChoosedVariant: 0

    property string textOfQuestion: "Это что за покемон неизвестная зверь тварь неясного сельского происхождения непонятной родословной???777"
    property string pathToImage: ""

    property string variant4Text: "" //"Вариант 4"
    property string variant4PathToImg: ""//"qrc:/icons/questpic.jpg"

    property string variant3Text: "" //"Вариант 3"
    property string variant3PathToImg: "" //"../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant2Text: "" //"Вариант 4"
    property string variant2PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property string variant1Text: "" //"Вариант 4"
    property string variant1PathToImg: "" // "../../../../YandexDisk/RushPolytech/icons/questpic.jpg"

    property int buttonSize: height / 2 / 4.2

    property string textOfNullTicket: appEngine.textOfNullTicket

    function sendAnswerToStatistic(indexOfChoosedVariant : int){
        if(textOfQuestion !== textOfNullTicket)
        {
            rootItem.saveAnswerInStatistic(ticketIndex, (indexOfCorrectVariant === indexOfChoosedVariant));
        }

        if((indexOfCorrectVariant === indexOfChoosedVariant))
            textOfQuestion += "\nВерно!";
        else
            textOfQuestion += "\nНеверно!";

    }

    Keys.onPressed: (event)=> {
                        switch(event.key)
                        {
                            case Qt.Key_1: variant1Button.clicked(); break;
                            case Qt.Key_2: variant2Button.clicked(); break;
                            case Qt.Key_3: variant3Button.clicked(); break;
                            case Qt.Key_4: variant4Button.clicked(); break;

                            case Qt.Key_Enter: variant1Button.clicked(); break;
                            case Qt.Key_Space: variant1Button.clicked(); break;
                            case Qt.Key_Return: variant1Button.clicked(); break;

                    }
                        event.accepted = true;
                    }

    MouseArea{
        anchors.fill: parent

        Item {
            id: imageWithBorder
            height: pathToImage === "" ? 1 : parent.height / 4

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 5
            anchors.topMargin: 10
            visible: pathToImage === "" ? false : true

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

            height: variant4Text !== "" || variant4PathToImg !== "" ? buttonSize : 1
            visible: variant4Text !== "" || variant4PathToImg !== ""

            property bool isButtonHighlited: false

            Rectangle {
                id: variant4ButtonHigliter
                visible: variant4Button.isButtonHighlited
                anchors.fill: parent

                anchors.bottomMargin: 4
                anchors.topMargin: 4

                color: "#7A9DBF"
                opacity: 0.3
                radius: 4
            }

            Text {
                id:variant4ButtonText
                text: variant4PathToImg === "" ? "4) "+variant4Text : ""
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
                visible: variant4PathToImg !== ""

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

            onClicked: {
                if(mainScreenRectangle.state !== "HighliteRightAnswer")
                {
                    mainScreenRectangle.state = "HighliteRightAnswer"
                    sendAnswerToStatistic(4);
                }
                else
                {
                    console.log("Переключаем на следующий");
                    view.pop(StackView.PushTransition);
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

            height: variant3Text !== "" || variant3PathToImg !== "" ? buttonSize : 1
            visible: variant3Text !== "" || variant3PathToImg !== ""

            property bool isButtonHighlited: false

            Rectangle {
                id: variant3ButtonHigliter
                visible: variant3Button.isButtonHighlited
                anchors.fill: parent

                anchors.bottomMargin: 4
                anchors.topMargin: 4

                color: "#7A9DBF"
                opacity: 0.3
                radius: 4
            }

            Text {
                id:variant3ButtonText
                text: variant3PathToImg === "" ? "3) "+variant3Text : ""
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
                visible: variant3PathToImg !== ""

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

            onClicked: {
                if(mainScreenRectangle.state !== "HighliteRightAnswer")
                {
                    mainScreenRectangle.state = "HighliteRightAnswer"
                    sendAnswerToStatistic(3);

                }
                else
                {
                    console.log("Переключаем на следующий");
                    view.pop(StackView.PushTransition);
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

            height: variant2Text !== "" || variant2PathToImg !== "" ? buttonSize : 1
            visible: variant2Text !== "" || variant2PathToImg !== ""

            property bool isButtonHighlited: false

            Rectangle {
                id: variant2ButtonHigliter
                visible: variant2Button.isButtonHighlited
                anchors.fill: parent

                anchors.bottomMargin: 4
                anchors.topMargin: 4

                color: "#7A9DBF"
                opacity: 0.3
                radius: 4
            }

            Text {
                id:variant2ButtonText
                text: (variant2PathToImg === "") ? "2) "+variant2Text : ""
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
                visible: variant2PathToImg !== ""
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

            onClicked: {
                if(mainScreenRectangle.state !== "HighliteRightAnswer")
                {
                    mainScreenRectangle.state = "HighliteRightAnswer"
                    sendAnswerToStatistic(2);
                }
                else
                {
                    console.log("Переключаем на следующий");
                    view.pop(StackView.PushTransition);
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

            height: variant1Text !== "" || variant1PathToImg !== "" ? buttonSize : 1
            visible: variant1Text !== "" || variant1PathToImg !== ""
            property bool isButtonHighlited: false

            Rectangle {
                id: variant1ButtonHigliter
                visible: variant1Button.isButtonHighlited
                anchors.fill: parent

                anchors.bottomMargin: 4
                anchors.topMargin: 4

                color: "#7A9DBF"
                opacity: 0.3
                radius: 4
            }

            Text {
                id:variant1ButtonText
                text: variant1PathToImg === "" ? "1) "+variant1Text : ""
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
                visible: variant1PathToImg !== ""

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

            onClicked: {
                if(mainScreenRectangle.state !== "HighliteRightAnswer")
                {
                    mainScreenRectangle.state = "HighliteRightAnswer"
                    sendAnswerToStatistic(1);
                }
                else
                {
                    console.log("Переключаем на следующий");
                    view.pop(StackView.PushTransition);
                }
            }
        }


        onClicked: {
            if(mainScreenRectangle.state === "HighliteRightAnswer")
            {

                console.log("Переключаем на следующий");
                view.pop(StackView.PushTransition);

            }
            else{
                console.log("Нажатие при активном вопросе");
            }
        }
    }


    states: [
        State {
            name: "HighliteRightAnswer"

            //button 1
            PropertyChanges {//если не мы правильный ответ шрифт - зачеркнутый, иначе норамальный
                target: variant1ButtonText
                font.strikeout: indexOfCorrectVariant !== 1
            }
            PropertyChanges {//если не мы правильный ответ, текущая кнопка полупрозрачная, иначе прозрачная
                target: variant1Button
                opacity: indexOfCorrectVariant !== 1? 0.5 : 1
                isButtonHighlited: indexOfCorrectVariant === 1
            }

            //button 2
            PropertyChanges {
                target: variant2ButtonText
                font.strikeout: indexOfCorrectVariant !== 2
            }
            PropertyChanges {
                target: variant2Button
                opacity: indexOfCorrectVariant !== 2? 0.5 : 1
                isButtonHighlited: indexOfCorrectVariant === 2
            }

            //button 3
            PropertyChanges {
                target: variant3ButtonText
                font.strikeout: indexOfCorrectVariant !== 3
            }
            PropertyChanges {
                target: variant3Button
                opacity: indexOfCorrectVariant !== 3? 0.5 : 1
                isButtonHighlited: indexOfCorrectVariant === 3
            }

            //button 4
            PropertyChanges {
                target: variant4ButtonText
                font.strikeout: indexOfCorrectVariant !== 4
            }
            PropertyChanges {
                target: variant4Button
                opacity: indexOfCorrectVariant !== 4? 0.5 : 1
                isButtonHighlited: indexOfCorrectVariant === 4
            }

        }
    ]//endStates
}



