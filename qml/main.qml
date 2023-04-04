import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: rootItem
    width: 420
    height: 736

    visible: true
    title: appEngine.title//qsTr("Hello World")




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
                        myAppHeader.state = "LearnScreen"
                        rootItem.startLearningSession();
                        //view.push("qrc:/qml/LSChooseVariant.qml")
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
                        myAppHeader.state = "ExamScreen"
                        view.push("qrc:/qml/LSInputValue.qml")
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


    }
}//end window
