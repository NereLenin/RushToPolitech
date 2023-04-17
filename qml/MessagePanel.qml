import QtQuick

Item {
    //вот тут панель с сообщением
    id:mainMessagePanelItem

    width: 40
    height: 1
    visible: false

    property bool isOpen: (mainMessagePanelItem.height > 1)
    property string textOfMessage: "Тестовый текст"
    property double openSize: 10;

    property int waitedTimeToClose: 10

    Timer {//если через 20 сек не закрыто, закроем сами
        id:myTimer
        interval: waitedTimeToClose * 1000; running: false; repeat: false
        onTriggered: mainMessagePanelItem.close()
    }

    function open(){
            myTimer.restart();//перезапускаем в любом случае, мог поменяться текст на уже открытом

            if(!isOpen)
            {
                mainMessagePanelItem.visible = true;//делаем видимым
                openCloseAnimation.start();//запускаем анимацию

            }
     }
    function close(){
            if(isOpen){
                myTimer.stop();
                mainMessagePanelItem.visible = true;//делаем видимым
                openCloseAnimation.start();//запускаем анимацию
            }
        }

    NumberAnimation on height {
            id: openCloseAnimation
            running: false
            from: mainMessagePanelItem.height > 1? mainMessagePanelItem.openSize : 1//если открытый анимация работает на закрытие до 1
            to:   mainMessagePanelItem.height > 1? 1 : mainMessagePanelItem.openSize//если закрытый анимация работает на открытие до openSize
    }

    MouseArea {
        id: mouse
        anchors.fill: mainMessagePanelItem

        onClicked: {
            openCloseAnimation.start()//так можно сделать только если он открытый и его видно, запускаем анимацию, сработает как закрытие
            }
    }

    Connections{
        target: openCloseAnimation

        function onStopped(){//когда анимация кончилась
            if(!(mainMessagePanelItem.height > 1))//если это анимация закрытия
                mainMessagePanelItem.visible = false;//делаем панельку невидимой
        }
    }

    Rectangle{
        anchors.fill: mainMessagePanelItem
        color: "#7A9DBF"

        Text {
            id: mainText
            text: mainMessagePanelItem.textOfMessage + "\n(нажмите чтобы закрыть)"

            anchors.fill: parent
            padding: 5

            color: "#383b39"
            styleColor: "#383b39"
            style: Text.Outline

            font.family: "Courier new"
            font.styleName: "Полужирный"

            font.pixelSize: 25
            fontSizeMode: Text.Fit

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
        }

    }

}
