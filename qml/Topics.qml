

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
    objectName: "topicsScreen"
    //anchors.fill: parent
    width: view.width
    height: view.height
    color: "#edecec"

    property bool showLearnTicketButton: true

    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        anchors.margins: 15
        anchors.bottomMargin: 20

        model: learningTopicsModel
        delegate: Topic {

            subtopic: showLearnTicketButton
            nameTopic: topicIndex + ". " + topicName
            //pathTopicIcon: myPathTopicIcon

            anchors.left: parent.left
            anchors.right: parent.right
            height: listView.height / 7

            onClicked: {
                //просмотр содержания
               }

            onInnerButtonClicked: {
                //вопросы по теме
                console.log(subjIndex, topicIndex);
                rootItem.showTopicsTickets(subjIndex, topicIndex);
            }

        }
        currentIndex: 1

        //нада шоб при увеличении экрана отражалось больше текста
    }
}
