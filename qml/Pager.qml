import QtQuick
import QtQuick.Controls

Item {
    id: rootPagerItem
    width: 10
    height: 30

    property string currentItem: view.currentItem.objectName

    property int currentTicketIndex: 0
    signal finishLearningSession();
    signal endLearningSession();

    function debugPush(page : string){
        view.push(page);
    }


    function goToNextScreenInLearningSession(){
        view.pop(StackView.PushTransition);
    }

    //возвращаемся к странице с которой начали обучение или экзамен или повтор
    function popToRegimeMainScreen(){

        switch(view.currentItem.objectName){
        case "topicsScreen"://если возвращаемся с скрина просмотра тем
        {
            console.log("pop subjectsScreen");
            view.popTo("subjectsScreen");
            return;
        }
        case "topicsTicketScreen"://если возвращаемся со скрина просмотра списка билетов в теме
        {
            console.log("pop topicsScreen");
            view.popTo("topicsScreen");
            return;
        }
        case "theoryScreen":
        {
            console.log("pop theoryScreen");
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

    function navigateTo(screenName : string){
        console.log("navigate")

        switch(screenName){
            case "FailedLearnScreen":
                view.countOfViewFinishScreen = 0;
                view.push("FailedLearnScreen.qml");
            return;
            case "RepeatScreen":
                view.countOfViewFinishScreen = 0;
                console.log("end on pop to repeat")
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

    function collectTicketInStack(ticketItem){
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

    StackView {
        id: view
        objectName: "mainStack"

        anchors.fill: parent
        initialItem: "qrc:/qml/StartScreen.qml"

        //вот это вот мерзость пизда просто, но
        //у нас первый раз стек видит финиш скрин когда мы его пушим в общей пачке
        //второй когда он пушен таймером или до него дошли из пачки
        //получается каждый раз когда мы его видим ВТОРОЙ раз у нас окончание учебной сессии
        property int countOfViewFinishScreen: 0
        property bool isFinishSessionFuncActive: true
        onCurrentItemChanged:
        {

            if(currentItem.objectName.includes("CV") || currentItem.objectName.includes("IV"))
            {
                currentTicketIndex = currentItem.ticketIndex
            }else{
                currentTicketIndex = 0;
            }

            //отслеживание finishScreen
            if(isFinishSessionFuncActive)
            {
            if(currentItem.objectName === "finishLearningScreen" ||
               currentItem.objectName === "finishExamScreen")
                view.countOfViewFinishScreen++;

            if(view.countOfViewFinishScreen > 1)
            {
                rootPagerItem.finishLearningSession();

                view.countOfViewFinishScreen = 0;
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



    }

}
