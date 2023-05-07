import QtQuick
import QtQuick.Controls

Item {
    id: rootPagerItem
    width: 10
    height: 30

    property string currentItem: view.currentItem.objectName

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

    function navigateTo(screenName : string){

        view.countOfViewFinishScreen = 0;
        switch(screenName){
            case "FailedLearnScreen":
                view.push("FailedLearnScreen.qml");
            break;
            case "RepeatScreen":
                endLearningSessions();
                if(view.depth > 1)
                    view.popTo("RepeatScreen")
                else
                    view.push("RepeatScreen.qml");
            break;
            case "StartScreen":
                endLearningSessions();
                view.popTo("StartScreen")
            break;
            case "subjectsScreen":
                view.push("Subjects.qml")
            break;
            case "topicsScreen":
                view.push("Topics.qml")
            break;
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
            //отслеживание finishScreen
            if(isFinishSessionFuncActive)
            {
            if(currentItem.objectName === "finishLearningScreen" ||
               currentItem.objectName === "finishExamScreen")
                view.countOfViewFinishScreen++;

            if(view.countOfViewFinishScreen > 1)
            {
                rootPagerItem.finishLearningSession();

                console.log("SessionFinish");
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
