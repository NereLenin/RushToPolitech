import QtQuick
import QtQuick.Controls

import TypeLearning 0.1

ApplicationWindow {
    id: rootItem
    width: 420
    height: 736
    objectName: "appMainScreen"

    visible: true
    title: appEngine.title


    function returnToRegimeMainPage(){
        appPager.popToRegimeMainScreen();
    }


    function navigateTo(screenName: string){
       appPager.navigateTo(screenName);
    }

    header: MyHeader{
        id: myAppHeader

        //жестко привязываем текущее состояние с именем экрана который сейчас отображается
        state: appPager.currentItem

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

    MessagePanel{
        id:myMessagePanel
        anchors.top: myAppHeader.bottom
        width: rootItem.width

        openSize: rootItem.height/12
        textOfMessage: "Этот текст бомба пуха правда подруха? Подуха, плюха, в штанах сухо, хуй мне в ухо"
    }

    Pager{//элемент отображения страниц, навигации
        id: appPager
        anchors.top: myMessagePanel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    Drawer {
        id: drawer
        y: myAppHeader.height
        width: parent.width * 0.4
        height: parent.height

        property double heightOfItemDriver: (drawer.height/9)+3.2

        Column {
            anchors.fill: parent

            ItemDelegate {//на главную
                width: parent.width
                height: drawer.heightOfItemDriver

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "На главную"

                    onClicked: {
                        rootItem.navigateTo("StartScreen")
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//учить
                width: parent.width
                height: drawer.heightOfItemDriver
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Учить"

                    onClicked: {
                        rootItem.startSession(LearnType.DefaultLearning);
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//повторить
                width: parent.width
                height: drawer.heightOfItemDriver

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Повторить"

                    onClicked: {
                        rootItem.navigateTo("RepeatScreen");

                        drawer.close()
                    }
                }
            }

            ItemDelegate {//экзамен
                width: parent.width
                height: drawer.heightOfItemDriver
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Экзамен"

                    onClicked: {
                        rootItem.startSession(LearnType.Exam);

                        drawer.close()
                    }
                }
            }

            ItemDelegate {//теория
                width: parent.width
                height: drawer.heightOfItemDriver
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Теория"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {//статистика
                width: parent.width
                height: drawer.heightOfItemDriver
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
                height: drawer.heightOfItemDriver
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
                height: drawer.heightOfItemDriver
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

    //начать учебную сессию
    signal startSession(type : int);

    //сигнал испускаемый при ответе, для сохранения данных в базе
    signal saveAnswerInStatistic(index: int, isCorrect : bool);

    //сигнал для завершения (и отчистки) всех текущих учебных сессий.
    signal endLearningSessions();

    //текущая учебная сессия на финальном экране со статистикой
    signal finishLearningSession();

    //сигнал для работы с тикетами которые неправильно ответили в ходе сесиии
    signal startLearnFailedTicketsSession();

    // --------слоты--------
    Connections { //для appEngine
        target: appEngine//класс бэка

        //слоты для заполнения стэка по сигналам с бэка

        //сохраняем в пагинатор тикет
        function onCollectLearningTicket(ticketItem){
            appPager.collectTicketInStack(ticketItem);
        }

        //отображаем сообщение в панели сообщений
        function onShowMessage(textOfMessage : string){
            myMessagePanel.textOfMessage = textOfMessage;
            myMessagePanel.open();            
        }

        //сохраняем в пагинатор экран окончания для данного режима
        function onPushFinalPage(){
            appPager.pushFinalPage()
        }

    }

    Connections { //для пагинатора
        target: appPager

        //если пагинатор кинул сигнал последнего экрана
        //в учебной сессии перенаправляем в бэк
        function onFinishLearningSession(){
            rootItem.finishLearningSession();
        }

        //если пагинатор кинул сигнал прерывания учеб сессии
        //перенаправляем в бэк
        function onEndLearningSession(){
            rootItem.endLearningSession();
        }
    }


}//end window
