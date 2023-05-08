import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material

Item {
    id: rootHeaderItem
    height: 80
    width: 500

    property bool showRightButton: false
    property int burgerLineHeight: 6
    property string headerText: "УТС"
    property string pathToRightIconButton: "qrc:/icons/studyIcon.png"
    property string headerTime: ""


    signal burgerButtonClicked()
    signal rightButtonClicked()


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
            flat: true

            onClicked: {
                rootHeaderItem.burgerButtonClicked();
            }
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

            onClicked: rootHeaderItem.rightButtonClicked()
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
        visible: (headerTime != "0:0" && headerTime != "00:00") && (!showRightButton)

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
        //------------хэдеры для самостоятельных экранов------------

        State {//хэдер начального экрана
            name: "StartScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "УТС"
                headerTime:""
            }
        },

        State {
            name: "RepeatScreen"//хэдер для страницы повторов
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Повтор"
                headerTime:""

            }
        },

        State {//хэдер для экрана отображения ошибочно решенных вопросов/билетов
            name: "FailedLearnScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Ошибки"
                headerTime:""

            }
        },

        State {
            name: "TheoryScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Тема 1 (12/20)"
                headerTime:""
                //headerTime: ""
            }
        },
        State {
            name: "subjectsScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Предметы"
                headerTime:""
                //headerTime: ""
            }
        },
        State {
            name: "topicsScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Темы"
                headerTime:""
                //headerTime: ""
            }
        },
        State {
            name: "topicsTicketScreen"
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Вопросы темы"
                headerTime:""
                //headerTime: ""
            }
        },


        //----------экраны с результатами

        State {
            name: "finishLearningScreen"//хэдер для экрана с результатами для просто учебы и всех остальных вариантов
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Результат"
                headerTime:""

            }
        },
        State {
            name: "finishExamScreen"//экран с результатами для экзамена

            PropertyChanges {
                target: rootHeaderItem

                showRightButton: false
                headerText: "Результат"
                headerTime:""

            }
        },

        //--------хэдеры для экранов выбора вварианта/ввода в разных режимах

        //----хэдеры экранов выбора вариантов-----

        //просто учеба
        State {
            name: "CVDefaultLearning"//хэдер для экрана выборов варианта для просто учебы
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Учим"
                headerTime:""
            }
        },
        State {
            name: "CVLearnFailed"//для отработки ошибчоных в сессии из просто учебы и экзамена
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Правим ошибки"
                headerTime:""

            }
        },

        //повтор
        State {
            name: "CVRepeatDefault"//повтор забытых, случайных, проблемных
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Повтор"
                headerTime:""

            }
        },
        State {
            name: "CVRepeatWithTimer"//повтор на время
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Повтор"
                headerTime: appEngine.timerTime

            }
        },
        State {
            name: "CVLearnFailedFromRepeat"//повтор ошибочных из сессии повторов
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Правим ошибки"
                headerTime:""

            }
        },

        //экзамен
        State {
            name: "CVExam"//экран выбора вариантов для экзамена
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: appEngine.currentTicketNumber + "/" + appEngine.countOfTicketsInSession
                headerTime: appEngine.timerTime

            }
        },

        //----хэдеры экранов ввода значения-----
        State {
            name: "IVDefaultLearning"//хэдер для экрана ввода значения для просто учебы
            PropertyChanges {
                target: rootHeaderItem

                showRightButton: true
                headerText: "Учим"
                headerTime:""
            }
        },

        State {
            name: "IVRepeatDefault"//для повторов
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Повтор"
                headerTime:""

            }
        },

        State {
            name: "IVLearnFailedFromRepeat"//экран для прогона ошибочных из повтора
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Правим ошибки"
                headerTime:""

            }
        },

        State {
            name: "IVLearnFailed"//экран для ввода значений из обучения
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: true
                headerText: "Правим ошибки"
                headerTime:""

            }
        },

        State {
            name: "IVRepeatWithTimer"//экран для ввода значений из повтора со временем
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: "Повтор"
                headerTime: appEngine.timerTime

            }
        },

        State {
            name: "IVExam"//экран для ввода значений из экзамена
            PropertyChanges {
                target: rootHeaderItem
                showRightButton: false
                headerText: appEngine.currentTicketNumber + "/" + appEngine.countOfTicketsInSession
                headerTime: appEngine.timerTime

            }
        }

    ]


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

