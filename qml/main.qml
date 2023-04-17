import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: rootItem
    width: 420
    height: 736
    objectName: "appMainScreen"

    visible: true
    title: appEngine.title//qsTr("Hello World")


    header: MyHeader{
        id: myAppHeader

        //жестко привязываем текущее состояние с именем экрана который сейчас отображается
        state: view.currentItem.objectName //Pager.currentItem

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

    //отдельный элемент пагинатор?
    StackView {
        id: view
        objectName: "mainStack"

        anchors.top: myMessagePanel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        initialItem: "qrc:/qml/StartScreen.qml"

        //вот это вот мерзость пизда просто, но
        //у нас первый раз стек видит финиш скрин когда мы его пушим в общей пачке
        //второй когда он пушен таймером или до него дошли из пачки
        //получается каждый раз когда мы его видим ВТОРОЙ раз у нас окончание учебной сессии
        property int countOfViewFinishScreen: 0
        property bool isFinishSessionFuncActive: true
        onCurrentItemChanged:
        {
            //отслеживание finishScreen
            if(isFinishSessionFuncActive)
            {
            if(currentItem.objectName === "finishLearningScreen" ||
               currentItem.objectName === "finishExamScreen")
                view.countOfViewFinishScreen++;

            if(view.countOfViewFinishScreen > 1)
            {
                rootItem.finishLearningSession();

                console.log("SessionFinish");
                countOfViewFinishScreen = 0;
            }
            }

          }

        //выгребаем все из стека до нужной страницы или до самой первой
        function popTo(objectNamePopTo : string)
        {
            //сбрасываем счетчик и отключаем отслеживание конца сессии пока
            //возвращаемся на маин скрин чтоб лишнего не насчитать
            countOfViewFinishScreen = 0;
            isFinishSessionFuncActive = false;

            while(view.currentItem.objectName !== objectNamePopTo && view.currentItem.objectName !== "StartScreen")
                view.pop();

            //потом включаем обратно
            isFinishSessionFuncActive = true;
        }

        //возвращаемся к странице с которой начали обучение или экзамен или повтор
        function popToRegimeMainScreen(){
            if(appEngine.typeOfCurrentSession === "RepeatWithTimer" ||//если это кто то из повторов
               appEngine.typeOfCurrentSession === "RepeatDefault" ||
               appEngine.typeOfCurrentSession === "LearnFailedFromRepeat")
            {
                view.popTo("RepeatScreen");//возвращаемся на экран повтора
            }
            else{
                view.popTo("StartScreen");//если это экзамен или просто учеба - возвращаемся на старотовый экран
            }

            }

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
                        //вместо всего этого
                        //Paginator.toStartScreen()
                        view.countOfViewFinishScreen = 0;
                        rootItem.endLearningSessions();             
                        view.popTo("StartScreen");

                        //myAppHeader.state = "MainScreen"
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
                        view.countOfViewFinishScreen = 0;
                        //myAppHeader.state = "LearnScreen"

                        rootItem.endLearningSessions();
                        rootItem.startLearningSession();
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
                        view.countOfViewFinishScreen = 0;
                        //myAppHeader.state = "RepeatScreen"

                        rootItem.endLearningSessions();
                        view.push("qrc:/qml/RepeatScreen.qml")
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
                        view.countOfViewFinishScreen = 0;
                        //myAppHeader.state = "ExamScreen";

                        rootItem.endLearningSessions();
                        rootItem.startExamSession();
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
                        view.countOfViewFinishScreen = 0;
                        rootItem.endLearningSessions();

                        view.push("qrc:/qml/LearnTheory.qml")
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
                        view.countOfViewFinishScreen = 0;
                        rootItem.endLearningSessions();

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
                        view.countOfViewFinishScreen = 0;
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
                        view.countOfViewFinishScreen = 0;
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

        //перенестив пагинатор
        function onCollectLearningTicket(ticketItem){

            if(ticketItem.type === "selectableAnswerTicket")
            {
                ticketItem.mixAnswers();
                view.push(["LSChooseVariant.qml",{"ticketIndex": ticketItem.ticketIndex,
                                                  "textOfQuestion": ticketItem.textOfQuestion,
                                                  "pathToImage": ticketItem.pathToImage,
                                                  "variant1Text": ticketItem.getAnswer(0),
                                                  "variant1PathToImg": ticketItem.getAnswerImageUrl(0),
                                                  "variant2Text": ticketItem.getAnswer(1),
                                                  "variant2PathToImg": ticketItem.getAnswerImageUrl(1),
                                                  "variant3Text": ticketItem.getAnswer(2),
                                                  "variant3PathToImg": ticketItem.getAnswerImageUrl(2),
                                                  "variant4Text": ticketItem.getAnswer(3),
                                                  "variant4PathToImg": ticketItem.getAnswerImageUrl(3),
                                                  "indexOfCorrectVariant": ticketItem.indexOfCorrectVariant
                                      }]);
            }else
            if(ticketItem.type === "inputAnswerTicket")
            {
                view.push(["LSInputValue.qml",{   "ticketIndex": ticketItem.ticketIndex,
                              "textOfQuestion": ticketItem.textOfQuestion,
                              "pathToImage": ticketItem.pathToImage,
                              "correctAnswer": ticketItem.correctAnswer}]);
            }
            else{
                console.log("Неизвестный билет немогу запушить");
                myMessagePanel.textOfMessage = "Неизвестный билет немогу запушить\n" + ticketItem.ticketIndex;
                myMessagePanel.open();
            }
        }


        //закидываем в стэк рандомную страничку
        function onPushStack(pageUrl : string){
            view.push(pageUrl);
        }

        function onShowMessage(textOfMessage : string){
            myMessagePanel.textOfMessage = textOfMessage;
            myMessagePanel.open();            
        }

    }

    //внутри QML
    function onReturnToRegimeMainPage(){
        console.log("return to main page");
        //вызов пагинатора
    }

    function onNavigateTo(screenName: string){
       //вызов пагинатора
    }
}//end window
