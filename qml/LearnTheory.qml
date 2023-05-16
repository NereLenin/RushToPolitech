

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: mainScreenRectangle

    objectName: "theoryScreen"

    width: view.width
    height: view.height
    color: "#edecec"

    //проверяем вызван ли экран из ответа на вопросы или нет
    property bool calledFromLearningTicket: rootItem.doLearnSomethingNow

    //данные о теории которую сейчас учим
    property int subjIndex: appEngine.topicControllerSubjIndex
    property int topicIndex: appEngine.topicControllerTopicIndex
    property string subjectIcon: appEngine.topicControllerSubjIcon

    //начало и конец подчеркивания для ответов на вопросы
    property int startHighlightPoint: appEngine.topicControllerHighlightStart
    property int endHighlightPoint: appEngine.topicControllerHighlighEnd

    //кусок текста темы из контроллера
    property string theoryText: appEngine.topicControllerMainText

    //текст с подсветкой
    property string highlightedText: theoryText.substring(0,startHighlightPoint) + "<u><i>" + theoryText.substring(startHighlightPoint,endHighlightPoint) + "</u></i>" + theoryText.substring(endHighlightPoint,theoryText.length)

    //если подсветка присутствует и нормальная, выводим ее, если нет то прост текст
    property string outputText: (endHighlightPoint > startHighlightPoint) && (endHighlightPoint <= theoryText.length) ? highlightedText : theoryText

    //изображение и вспомогательные переменные для их отображения
    property string imageURL: appEngine.topicControllerImageUrl
    property bool haveImage: imageURL !== ""

    property bool isImageUp: ((appEngine.topicControllerCurrentPage % 2) !== 0 )

    //контролим панель навигации от текущей страницы в контроллере
    onTheoryTextChanged:
    {
        switch(appEngine.topicControllerCurrentPage)
        {
        case 1:
            navigatePanel.state = "FirstPage";

            if(appEngine.topicControllerCountOfPages === 1)
                navigatePanel.state = "OnePageText";

            break;
        case appEngine.topicControllerCountOfPages:
            navigatePanel.state = "LastPage";
            break;
        default: navigatePanel.state = "SomewhereMiddleInText"; break;
        }
    }

    //переключаем страницы по стрелочкам
    Keys.onPressed: (event)=> {
                        switch(event.key)
                        {
                            case Qt.Key_Left:
                            if(prevButtonItem.visible)
                                prevButtonItemButton.clicked()
                            break;

                            case Qt.Key_Right:
                            if(nextButtonItem.visible)
                                nextButtonItemButton.clicked()
                            break;
                        }

                        event.accepted = true;
                    }


    Item {//верхняя картинка
        id: upImageWithBorder
        visible: haveImage && isImageUp //отображаем только если выпало изображение сверху и оно вообще есть

        height: (haveImage && isImageUp)? (parent.height / 4) : 1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20

        Rectangle {
            id: upImageBorder
            anchors.fill: parent
            border.color: "#7A9DBF"
            opacity: 0.6
        }

        Image {
            id: upImage

            anchors.fill: upImageBorder
            opacity: 1
            source: imageURL
            mirror: false
            fillMode: Image.PreserveAspectFit
        }
    }

    Text {//основной текст
        id: textOfTheory
        text: outputText
        anchors.top: upImageWithBorder.bottom
        anchors.bottom: downImageWithBorder.top

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10

        anchors.leftMargin: 5
        anchors.rightMargin: 5
        padding: 10

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.family: "Courier new"
        font.pixelSize: 32
        font.styleName: "Полужирный"
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap

        style: Text.Outline
        styleColor: "#383b39"
        color: "#383b39"
    }

    Item {//нижняя картинка
        id: downImageWithBorder
        visible: haveImage && !isImageUp

        height: (haveImage && !isImageUp)? (parent.height / 4) : 1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: navigatePanel.top
        anchors.margins: 20

        Rectangle {
            id: downImageBorder
            anchors.fill: parent
            border.color: "#7A9DBF"
            opacity: 0.6
        }

        Image {
            id: downImage

            anchors.fill: downImageBorder
            opacity: 1
            source: imageURL
            mirror: false
            fillMode: Image.PreserveAspectFit
        }
    }

    Item{//панель навигации (лево право)
        id:navigatePanel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: parent.height/7

        Rectangle {
            id: separatorLine
            anchors.left: prevButtonItem.left
            anchors.right: nextButtonItem.right
            anchors.bottom: nextButtonItem.top
            anchors.bottomMargin: 10

            height: 2

            color: "#7A9DBF"
            opacity: 0.6
        }

        property int buttonHeight: (height / 1.5)//размер кнопок на панели

        Item {
            id: prevButtonItem

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter

            anchors.margins: 15
            anchors.bottomMargin: 15
            anchors.rightMargin: 10

            height: navigatePanel.buttonHeight

            property string buttonText: "<"
            property string iconURL: ""

            Button {
                id: prevButtonItemButton
                anchors.fill: parent

                font.family: "Courier new"
                font.pointSize: 14
                font.styleName: "Полужирный"
                font.bold: true

                onClicked: {
                    if(navigatePanel.state !== "FirstPage" && navigatePanel.state !== "OnePageText" )
                    {
                        rootItem.topicPreviousPage();
                    }
                    else
                        rootItem.returnToRegimeMainPage();
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "#cc0061c0"
                radius: 5
                opacity: 0.5
            }

            Text {
                visible: prevButtonItem.iconURL == ""
                text: prevButtonItem.buttonText

                anchors.fill: parent

                anchors.left: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                style: Text.Outline
                scale: 1

                anchors.rightMargin: 5
                anchors.topMargin: 0

                font.styleName: "Полужирный"
                padding: 5
                fontSizeMode: Text.Fit
                font.family: "Courier new"
                textFormat: Text.PlainText
                font.pixelSize: 25

                styleColor: "#383b39"
            }

            Image {
                visible: prevButtonItem.iconURL != ""
                anchors.fill: parent
                anchors.margins: 10
                opacity: 1
                source: prevButtonItem.iconURL
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: nextButtonItem

            anchors.bottom: parent.bottom
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right

            anchors.margins: 15
            anchors.bottomMargin: 15
            anchors.leftMargin: 10

            height: navigatePanel.buttonHeight

            property string buttonText: ">"
            property string iconURL: ""

            Button {
                id: nextButtonItemButton
                anchors.fill: parent

                font.family: "Courier new"
                font.pointSize: 14
                font.styleName: "Полужирный"
                font.bold: true

                onClicked: {

                    if(navigatePanel.state !== "LastPage")
                        rootItem.topicNextPage();
                    else
                        if(!calledFromLearningTicket)
                        {
                            rootItem.showTopicsTickets(subjIndex, topicIndex);
                        }

                }
            }

            Rectangle {
                anchors.fill: parent
                color: "#cc0061c0"
                radius: 5
                opacity: 0.5
            }

            Text {
                text: nextButtonItem.buttonText
                visible: nextButtonItem.iconURL == ""

                anchors.fill: parent

                anchors.left: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                style: Text.Outline
                scale: 1

                anchors.rightMargin: 5
                anchors.topMargin: 0

                font.styleName: "Полужирный"
                padding: 5
                fontSizeMode: Text.Fit
                font.family: "Courier new"
                textFormat: Text.PlainText
                font.pixelSize: 25

                styleColor: "#383b39"
            }

            Image {
                anchors.fill: parent
                visible: nextButtonItem.iconURL != ""
                anchors.margins: 10
                opacity: 1
                source: nextButtonItem.iconURL
                fillMode: Image.PreserveAspectFit
            }
        }

        states: [//меняем состояния панели, если на первом экране, левая кнопка ведет назад, если на последнем, правая кнопка ведет к темам или к билету который учили


            State {//панель на первой странице
                name: "FirstPage"
                PropertyChanges {
                    target: nextButtonItem
                    iconURL: ""
                }
                PropertyChanges {
                    target: prevButtonItem
                    iconURL: calledFromLearningTicket? "qrc:/icons/bilets.png" : subjectIcon //если отвечали на вопрос показываем иконку учебы билетов, если из теории читать начали, показываем иконку предмета
                }
            },
            State {//панель при чтении текста посередине
                name: "SomewhereMiddleInText"
                PropertyChanges {
                    target: nextButtonItem
                    iconURL: ""
                }

                PropertyChanges {
                    target: prevButtonItem
                    iconURL: ""
                }
            },
            State {//панель при чтении последней страницы
                name: "LastPage"
                PropertyChanges {
                    target: nextButtonItem
                    iconURL: "qrc:/icons/bilets.png"
                    visible: !calledFromLearningTicket
                }

                PropertyChanges {
                    target: prevButtonItem
                    iconURL: ""
                }
            },
            State {//Если первая страничка и есть последняя страничка
                name: "OnePageText"
                PropertyChanges {
                    target: nextButtonItem
                    iconURL: ""
                    visible:false
                }

                PropertyChanges {
                    target: prevButtonItem
                    iconURL: calledFromLearningTicket? "qrc:/icons/bilets.png" : subjectIcon
                }
            }//endstate
        ]//endstates
    }

}
