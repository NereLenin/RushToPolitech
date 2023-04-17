//LS - Learn Screen
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: mainScreenRectangle
    objectName: "IV" + appEngine.typeOfCurrentSession
    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    property int ticketIndex: 0
    property string correctAnswer: "жепич"
    property string textOfQuestion: "Это что за покемон неизвестная зверь тварь неясного сельского происхождения непонятной родословной???777"
    property string pathToImage: "qrc:/icons/learning.png"

    Keys.onPressed: (event)=> {
            if (event.key === Qt.Key_Enter  ||
                event.key === Qt.Key_Space  ||
                event.key === Qt.Key_Return ||
                event.key === Qt.Key_Right)
                {
                submitItemButton.clicked()
                event.accepted = true;
                }
    }

    MouseArea{
        anchors.fill: parent




        Item {
            id: submitButtonItem

            height: (parent.height / 2) / 4.2

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 15
            anchors.bottomMargin: 20

            Button {
                id: submitItemButton//Чо за нейминг ты чо бля ебанулся дядь
                anchors.fill: parent

                font.family: "Courier new"
                font.pointSize: 14
                font.styleName: "Полужирный"
                font.bold: true
                onClicked: {
                    if(mainScreenRectangle.state === "RightAnswer" || mainScreenRectangle.state === "WrongAnswer")
                    {
                        console.log("Переключаем на следующий (кнопка)");
                        view.pop(StackView.PushTransition);
                    }
                    else{
                        console.log("Нажатие при активном вопросе(кнопка)");
                        let myLowCaseAnswer = myTextField.text.replace(",", ".").toLowerCase();

                        let rightLowCaseAnswer = correctAnswer.toLowerCase();
                        if(myLowCaseAnswer === rightLowCaseAnswer)
                        {
                            mainScreenRectangle.state = "RightAnswer"
                            textOfQuestion += "\nВерно!"
                        }
                        else{
                            mainScreenRectangle.state = "WrongAnswer"
                            textOfQuestion += "\nНеверно!"
                        }
                        rootItem.saveAnswerInStatistic(ticketIndex, (myLowCaseAnswer === rightLowCaseAnswer));
                    }


                }
            }

            Rectangle {
                anchors.fill: parent
                color: "#cc0061c0"
                radius: 5
                opacity: 0.5
            }

            Text {
                text: "Ответить"

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

    Rectangle {
        id: separatorLine
        anchors.left: inputTextRectangle.left
        anchors.right: inputTextRectangle.right
        anchors.bottom: inputTextRectangle.top
        anchors.bottomMargin: 10

        height: 2

        color: "#7A9DBF"
        opacity: 0.6
    }

    Text {
        id: fullTextOfQuestion
        text: textOfQuestion

        //height: (parent.height / 2) / 1.5
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

    Item {
        id: imageWithBorder
        height: pathToImage == "" ? 1 : parent.height / 3

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
            id: image
            anchors.fill: imageBorder
            anchors.margins: 10
            opacity: 1
            source: pathToImage

            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: inputTextRectangle
        height: submitButtonItem.height

        anchors.left: submitButtonItem.left
        anchors.right: submitButtonItem.right
        anchors.bottom: submitButtonItem.top
        anchors.bottomMargin: 10
        anchors.topMargin: 10


        TextField {
            id: myTextField
            color: "#383b39"

            anchors.fill: parent

            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            activeFocusOnTab: true
            focus: true
            hoverEnabled: true
            font.styleName: "Полужирный"
            font.family: "Courier New"

            placeholderTextColor: "#383b39"
            selectedTextColor: "#7A9DBF"
            Material.accent: "#cc0061c0"




        }
        Text {
            id:myPlaceHolder
            anchors.fill: myTextField
            text: "Введите ответ..."
            color: "#383B39"
            font.pixelSize: 25
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Полужирный"
            font.family: "Courier New"
            visible: !myTextField.text

        }

        MouseArea{//включается только когда ответ уже выбран чтобы переключить на следующий
        anchors.fill: parent
        visible: mainScreenRectangle.state === "RightAnswer" || mainScreenRectangle.state === "WrongAnswer"
        enabled: mainScreenRectangle.state === "RightAnswer" || mainScreenRectangle.state === "WrongAnswer"
        onClicked:
        {
            console.log("Переключаем на следующий (текстовое поле)");
            view.pop(StackView.PushTransition);
        }

        }



    }

    onClicked: {
        if(mainScreenRectangle.state === "RightAnswer" || mainScreenRectangle.state === "WrongAnswer")
        {
            console.log("Переключаем на следующий(осн экран)");
            view.pop(StackView.PushTransition);
        }
        else{
            console.log("Нажатие при активном вопросе(осн экран)");
        }
    }


    }

    states: [
        State {
            name: "RightAnswer"
            PropertyChanges {
                target: myTextField
                readOnly:true
                color: "#cc0061c0"
            }
        },
        State {
            name: "WrongAnswer"
            PropertyChanges {
                target: myPlaceHolder
                visible: true
                text: correctAnswer
                color: "#cc0061c0"
                style: Text.Outline
                styleColor: "#cc0061c0"
            }
            PropertyChanges {
                target: myTextField
                opacity: 0.2
                font.strikeout: true
                readOnly: true
            }


        }
    ]


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

