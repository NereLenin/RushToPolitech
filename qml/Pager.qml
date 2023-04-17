import QtQuick
import QtQuick.Controls

Item {
    id: rootItem
    width: 10
    height: 30

    property string currentItem: view.currentItem.objectName

    signal finishLearningSession();

    function navigateTo(screenName : string){
        switch(screenName){
            case "FailedLearnScreen": view.push("FailedLearnScreen.qml"); break;
            case "finishExamScreen": view.push("finishExamScreen.qml"); break;
            case "finishExamScreen": view.push("finishExamScreen.qml"); break;
        default: break;
        }
    }


    StackView {
        id: view
        objectName: "mainStack"

        width:rootItem.width
        height: rootItem.height

        //anchors.top: myMessagePanel.bottom
        //anchors.left: parent.left
        //anchors.right: parent.right
        //anchors.bottom: parent.bottom
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
                finishLearningSession();

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
}
