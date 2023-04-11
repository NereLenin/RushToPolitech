import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: rootItem
    width: 420
    height: 736

    visible: true
    title: appEngine.title//qsTr("Hello World")

    Component.onCompleted:
    {
        view.push("qrc:/qml/FinishExamFailed.qml");
    }



    header: MyHeader{
        id: myAppHeader
        state: "MainScreen"
        x:0
        y:0
        anchors.left: parent.left
        anchors.right: parent.right


        height: parent.height / 12

        onBurgerButtonClicked: {
            console.log("burg button");
            if(drawer.opened)
            {
                console.log("draw close");
                drawer.close();

            }
            else
            {
                console.log("draw open");
                drawer.visible = true;
                drawer.open();
                drawer.visible = true;
            }

        }
    }


    StackView {
        id: view
        objectName: "mainStack"

        anchors.top: myAppHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        initialItem: "qrc:/qml/StartScreen.qml"

        //вот это вот мерзость пизда просто, но
        //у нас первый раз стек видит финиш скрин когда мы его пушим в общей пачке
        //второй когда он пушен таймером или до него дошли из пачки
        //получается каждый раз когда мы его видим ВТОРОЙ раз у нас окончание учебной сессии
        property int countOfViewFinishScreen: 0
        onCurrentItemChanged:
        {
            if(currentItem.objectName === "finishLearningScreen")
                countOfViewFinishScreen++;

            if(countOfViewFinishScreen == 2)
            {
                rootItem.finishLearningSession();
                console.log("SessionFinish");
                countOfViewFinishScreen = 0;
            }
        }

    }

    Drawer {
        id: drawer
        y: myAppHeader.height
        width: parent.width * 0.4
        height: parent.height

        Column {
            anchors.fill: parent

            ItemDelegate {//на главную
                width: parent.width
                height: parent.height/14

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "На главную"

                    onClicked: {
                        rootItem.endLearningSessions();

                        myAppHeader.state = "MainScreen"
                        view.push("qrc:/qml/StartScreen.qml")
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//учить
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Учить"

                    onClicked: {
                        rootItem.endLearningSessions();

                        myAppHeader.state = "LearnScreen"
                        rootItem.startLearningSession();
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//повторить
                width: parent.width
                height: parent.height/14

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Повторить"

                    onClicked: {
                        rootItem.endLearningSessions();

                        myAppHeader.state = "RepeatScreen"
                        view.push("qrc:/qml/RepeatScreen.qml")
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//экзамен
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Экзамен"

                    onClicked: {
                        rootItem.endLearningSessions();

                        myAppHeader.state = "ExamScreen"
                        rootItem.startExamSession();
                        //view.push("qrc:/qml/LSInputValue.qml")
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//теория
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Теория"

                    onClicked: {
                        rootItem.endLearningSessions();

                        myAppHeader.state = "TheoryScreen"
                        view.push("qrc:/qml/LearnTheory.qml")
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//статистика
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Статистика"

                    onClicked: {
                        rootItem.endLearningSessions();

                        drawer.close()
                    }
                }
            }

            ItemDelegate {//настройки
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Настройки"

                    onClicked: {
                        rootItem.endLearningSessions();

                        drawer.close()
                    }
                }
            }

            ItemDelegate {//выход
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Выход"

                    onClicked: {
                        rootItem.endLearningSessions();

                        drawer.close()
                    }
                }
            }
        }//endcolumn

    }//end drawer


    /*          сигналы и слоты для взаимодействия с бэком        */

    // --------сигналы--------

    //сигнал испускаемый при ответе, для сохранения данных в базе
    signal saveAnswerInStatistic(index: int, isCorrect : bool);

    //сигнал для начала сессии "учить"
    signal startLearningSession();

    //сигнал для начала сессии "повтор сложных"
    signal startRepeatHardSession();

    //сигнал для начала сессии "повтор на время"
    signal startRepeatWithTimerSession();

    //сигнал для начала сессии "повтор случайных"
    signal startRepeatRandomSession();

    //сигнал для начала сессии "повтор забытых"
    signal startRepeatForgottenSession();

    //сигнал для начала сессии "сдача экзамена"
    signal startExamSession();

    //сигнал для завершения (и отчистки) всех текущих учебных сессий.
    signal endLearningSessions();

    //текущая учебная сессия на финальном экране со статистикой
    signal finishLearningSession();

    //сигнал для работы с тикетами которые неправильно ответили в ходе сесиии
    signal startLearnFailedTicketsSession();

    // --------слоты--------
    Connections {
        target: appEngine//класс бэка

        //слоты для заполнения стэка по сигналам с бэка
        //закидываем в стэк страничку с выбором варианта
        function onPushSelectable( index : int,
                                    textOfQuestion, pathToImage,
                                    variant1Text, variant1PathToImg,
                                    variant2Text, variant2PathToImg,
                                    variant3Text, variant3PathToImg,
                                    variant4Text, variant4PathToImg : string,
                                    indexOfCorrectVariant : int )
        {
            view.push("LSChooseVariant.qml",{"ticketIndex": index,
                          "textOfQuestion": textOfQuestion,
                          "pathToImage": pathToImage,
                          "variant1Text": variant1Text,
                          "variant1PathToImg": variant1PathToImg,
                          "variant2Text": variant2Text,
                          "variant2PathToImg": variant2PathToImg,
                          "variant3Text": variant3Text,
                          "variant3PathToImg": variant3PathToImg,
                          "variant4Text": variant4Text,
                          "variant4PathToImg": variant4PathToImg,
                          "indexOfCorrectVariant": indexOfCorrectVariant
                      });
        }

        //закидываем в стэк страничку с вводом
        function onPushInputable(index : int, correctAnswer, textOfQuestion, pathToImage: string)
        {
            view.push("LSInputValue.qml",{   "ticketIndex": index,
                          "textOfQuestion": textOfQuestion,
                          "pathToImage": pathToImage,
                          "correctAnswer": correctAnswer});
        }

        //закидываем в стэк рандомную страничку
        function onPushStack(pageUrl : string){
            view.push(pageUrl);
        }

        function onClearStack(){
            view.clear();
        }
    }
}//end window
