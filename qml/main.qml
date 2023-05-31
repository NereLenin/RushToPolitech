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

    Component.onCompleted: {
        //appPager.debugPush("LearnTheory.qml");
    }

    property bool doLearnSomethingNow: appPager.isLearningSomethingRightNow

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

        onRightButtonClicked: {//обработка нажатия на правую кнопку в хэдере
            switch(state)
            {
            case "topicsScreen"://если на экране с списоком тем, возвращаемся на список предметов
                appPager.popToRegimeMainScreen();
                return;

            case "subtopicsTicketScreen"://если на экране со списком билетов темы, возвращаемся на список тем предмета
                appPager.popToRegimeMainScreen();
                return;
            case "subtopicsScreen"://если на экране со списком билетов темы, возвращаемся на список тем предмета
                appPager.popToRegimeMainScreen();
                return;
            case "theoryScreen"://если на содержании темы, возвращаемся на список тем
                appPager.popToRegimeMainScreen();
                return;

            default:
            {
                if(learningSomething && !state.includes("LearnTicketsInTopic") )//если сейчас происходит учеба то показываем теорию для текущего билета
                {
                    console.log(state)
                    rootItem.showSubtopicForTicket(appPager.currentTicketIndex)
                }
                else{
                    appPager.popToRegimeMainScreen();
                }
            }
            break;

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
                        rootItem.showSubjects();
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

    //функции-связки между страницами в стеке и пагинатором, чтоб не вызывать напрямую

    function returnToRegimeMainPage()//вернуться на основную страницу, в зависимости от того где мы (в теории, учим билеты и т.д.)
    {
        appPager.popToRegimeMainScreen();
    }

    function navigateTo(screenName: string)//перейти на страницу
    {
        appPager.navigateTo(screenName);
    }

    function toNextTicket()//переключиться на следующий билет во время учебной сессии
    {
        appPager.goToNextScreenInLearningSession();
    }

    /*          сигналы и слоты для взаимодействия с бэком        */

    // --------сигналы--------

    //------ To Learning Session-----//
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


    //------ To Theory-----//
    //отображение только одоного билета без запись в статистику
    signal showSingleTicket(ticketIndex : int);

    //сигнал для подготовки листа под страницу отображения предметов
    signal showSubjects();

    //сигнал для подготовки листа тем в предмете
    signal showTopics(subjectIndex : int);

    //сигнал для подготовки листа подтем в теме
    signal showSubtopics(subjectIndex : int, topicIndex : int);

    //сигнал для подготовки данных о билетах, ответы которых есть в подтеме
    signal showSubtopicTickets(subjectIndex : int, topicIndex : int, subtopicIndex : int);

    //------ To Theory Topic Controller -----//
    //просмотр СОДЕРЖАНИЯ темы
    signal showSubtopic(subjectIndex : int, topicIndex : int, subtopicIndex : int);

    //просмотр СОДЕРЖАНИЯ темы для тикета(сам переключит где ответ в теме)
    signal showSubtopicForTicket(ticketIndex  : int);

    //переключение след/предыдущую страницу
    signal subtopicNextPage();
    signal subtopicPreviousPage();


    // --------слоты--------

    Connections { //для appEngine
        target: appEngine//класс бэка

        //отображаем сообщение в панели сообщений
        function onShowMessage(textOfMessage : string){
            myMessagePanel.textOfMessage = textOfMessage;
            myMessagePanel.open();
        }

        //слоты для заполнения стэка по сигналам с бэка

        //сохраняем в пагинатор тикет
        function onCollectLearningTicket(ticketItem){
            appPager.collectTicketInStack(ticketItem);
        }

        //сохраняем в пагинатор экран окончания для данного режима
        function onPushFinalPage(){
            appPager.pushFinalPage()
        }

        //Бэк говорит что данные для отображения страниц готовы
        function onSubjectsDataIsReady()//список предметов готов, можно показывать страницу
        {
            appPager.navigateTo("subjectsScreen")
        }

        function onTopicsDataIsReady()//список тем в предмете готов можно показывать
        {
            appPager.navigateTo("topicsScreen")
        }

        function onSubtopicTicketsDataIsReady()//список билетов для темы
        {
            appPager.navigateTo("subtopicsTicketScreen")
        }

        function onSubtopicsDataIsReady(){
            appPager.navigateTo("subtopicsScreen")
        }

        function onSubtopicDataIsReady()//содержание темы готово, отображаем
        {
            appPager.navigateTo("theoryScreen")
        }

        function onTicketSubtopicDataIsReady()//содержание темы для билета готовы
        {
            appPager.navigateTo("theoryScreen")
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
