import QtQuick
import QtQuick.Controls

Item {
    id: rootPagerItem
    width: 10
    height: 30

    //----------свойства----------//
    property string currentItem: view.currentItem.objectName

    //активна ли учебная сессия сейчас(меняется в событии стека при смене экрана)
    property bool isLearningSomethingRightNow: false

    //на экране ли мы ответа на вопрос(тож)
    property bool isThisScreenLearningScreen: false

    //если сейчас на экране ответа на вопрос, номер вопроса здесь
    property int currentTicketIndex: 0

    //если ответил все вопросы до конца и нужно останавливать таймеры, обновлять статистику и т.д.
    signal finishLearningSession();

    //удаляем текущую учебнуй сессию
    signal endLearningSession();

    //----------функции----------//
    function debugPush(page : string)
    {
        view.push(page);
    }

    function goToNextScreenInLearningSession()//для экранов выбора ответа на вопрос, чтоб перейти на следующий
    {
        view.pop(StackView.PushTransition);
    }

    //возвращаемся к странице с которой начали обучение или экзамен или повтор
    function popToRegimeMainScreen(){

        switch(view.currentItem.objectName){
        case "topicsScreen"://если возвращаемся с скрина просмотра тем
        {
            view.popTo("subjectsScreen");
            return;
        }
        case "topicsTicketScreen"://если возвращаемся со скрина просмотра списка билетов в теме
        {
            view.popTo("topicsScreen");
            return;
        }
        case "theoryScreen"://если содержимое темы читаем
        {
            view.pop();//весь просмотр теории всегда на одной странице, как бы мы на него не попали, выход с него - чисто одним попом
            return;
        }
        default:
        {
            if(appEngine.typeOfCurrentSession === "RepeatWithTimer" ||//если это кто то из повторов
               appEngine.typeOfCurrentSession === "RepeatDefault"   ||
               appEngine.typeOfCurrentSession === "LearnFailedFromRepeat")
            {
                view.popTo("RepeatScreen");//возвращаемся на экран повтора
                console.log("pop repeat");
            }
            else
            {
                view.popTo("StartScreen");//если это экзамен или просто учеба - возвращаемся на старотовый экран
            }

        }
        break;

        }

    }

    //переместится на страницу
    function navigateTo(screenName : string){
        console.log("navigate")

        switch(screenName){
            case "FailedLearnScreen":
                view.countOfViewFinishScreen = 0;
                view.push("FailedLearnScreen.qml");
            return;
            case "RepeatScreen":
                view.countOfViewFinishScreen = 0;
                endLearningSessions();
                if(view.depth > 1)
                    view.popTo("RepeatScreen")
                if(view.currentItem.objectName !== "RepeatScreen")
                    view.push("RepeatScreen.qml");
            return;
            case "StartScreen":
                view.countOfViewFinishScreen = 0;
                console.log("end on pop to start")
                endLearningSessions();
                view.popTo("StartScreen")
            return;
            case "subjectsScreen":
                view.countOfViewFinishScreen = 0;
                view.push("Subjects.qml")
            return;
            case "topicsScreen":
                view.countOfViewFinishScreen = 0;
                view.push("Topics.qml")
            return;
            case "topicsTicketScreen":
                view.countOfViewFinishScreen = 0;
                view.push("TicketsOfTopic.qml")
            return;
            case "theoryScreen":
                view.push("LearnTheory.qml")
            return;
        default: break;
        }

    }

    //по режиму определяем экран конца обучения
    function pushFinalPage()
    {
        if(appEngine.typeOfCurrentSession === "Exam")
        {
          view.push("FinishExamScreen.qml");//for exam
        }
        else//for else screen
        {
          view.push("FinishLearnScreen.qml");
        }

    }

    function collectTicketInStack(ticketItem){//сигналом с бэка приходит информация о ticketItem, засовываем в стек страничку с такими параметрами
        if(ticketItem.type === "selectableAnswerTicket")
        {
            //если экран с выбором варианта
            ticketItem.mixAnswers();//перемешиваем ответы, чтоб не повторялись и тяжелей запомнить
            //отправляем в стек
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
            //если экран с вводом значения
            view.push(["LSInputValue.qml",{   "ticketIndex": ticketItem.ticketIndex,
                          "textOfQuestion": ticketItem.textOfQuestion,
                          "pathToImage": ticketItem.pathToImage,
                          "correctAnswer": ticketItem.correctAnswer}]);
        }
        else
        {
            console.log("Неизвестный билет немогу запушить");
            myMessagePanel.textOfMessage = "Неизвестный билет немогу запушить\n" + ticketItem.ticketIndex;
            myMessagePanel.open();
        }
    }

    //------------------Компоненты-----------------//

    StackView {
        id: view
        objectName: "mainStack"

        anchors.fill: parent
        initialItem: "qrc:/qml/StartScreen.qml"

        //----------свойства------------//

        //счетчик количества посл экранов в сессии, увеличивается на 1 когда в currentItem у нас посл экран, увеличивается раз когда прилетает пачка с вопросами и посл экраном, второй раз когда мы все прорешали(вытащили из стека) и дошли до него
        property int countOfViewFinishScreen: 0

        //управляет насчитыванием верхнего счетчика, если тру - считается, если false не считается, нужна для корректного popTo
        property bool isFinishSessionFuncActive: true

        //это последний экран в сессии, включается когда countOfViewFinishScreen > 1
        property bool isCurrentScreenIsFinishScreenInSession: false

        //-----------функции--------------//
        function updateFlags(){
            //обновляем флаг, отмечающий учим сейчас что ни будь или нет
            isLearningSomethingRightNow = ((appEngine.typeOfCurrentSession).toLowerCase().includes("learn") || (appEngine.typeOfCurrentSession).toLowerCase().includes("repeat"));//(currentItem.includes("learn")) || (currentItem.includes("repeat"))

            //флаг того что мы прям на экране ответа на билет во время учебной сессии
            isThisScreenLearningScreen = currentItem.objectName.includes("CV") || currentItem.objectName.includes("IV")
        }

        function updateCurrentTicket()
        {
            if(isThisScreenLearningScreen)
                currentTicketIndex = currentItem.ticketIndex
            else
                currentTicketIndex = 0;
        }

        function updateFinishScreenView(){
            //отслеживание finishScreen
            if(isFinishSessionFuncActive)
            {
            if(currentItem.objectName === "finishLearningScreen" ||
               currentItem.objectName === "finishExamScreen")
                view.countOfViewFinishScreen++;

            //при заполнении стека на учебу финальный экран на некоторое время оказывается текущим,
            //и счетчик countOfViewFinishScreen увеличивается на 1
            //когда мы ВО ВТОРОЙ раз видим финиш скрин - значит или время вышло и его запушило, или мы всю пачку скринов из стека проучили
            //поэтому если count > 1 значит мы на посл экране во второй раз и нужно остановить учебную сессию
            if(view.countOfViewFinishScreen > 1)
            {
                isCurrentScreenIsFinishScreenInSession = true;
                view.countOfViewFinishScreen = 0;
            }
            else
                isCurrentScreenIsFinishScreenInSession = false;
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

        //---------Слоты-------------//

        onCurrentItemChanged://ПРИ СМЕНЕ ЭКРАНА
        {
            //обновляем флаги
            updateFlags();

            //обновляем текущий изучаемый билет(если ниче не учим он 0)
            updateCurrentTicket();

            //обновляем отслеживание экран ли это конца сессии
            updateFinishScreenView();

            //если да, сообщаем об этом сигналом
            if(isCurrentScreenIsFinishScreenInSession)
            {
                rootPagerItem.finishLearningSession();
            }
        }



    }//endStack

}
