

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import RushPoliTech
import QtQuick.Studio.Components 1.0

Rectangle {
    id: mainScreenRectangle

    width: 420
    height: 736
    anchors.fill: parent
    color: "#edecec"

    ListView {
        id: listView
        anchors.fill: parent
        clip: true
        anchors.margins: 15
        anchors.bottomMargin: 20

        model: ListModel {
            ListElement {
                myNameTopic: "Программирование"
                myPathTopicIcon: "../../../../YandexDisk/RushPolytech/icons/theory.png"
                mySubtopic: false
            }

            ListElement {
                myNameTopic: "Автоматизация"
                myPathTopicIcon: "../../../../YandexDisk/RushPolytech/icons/automatic.png"
                mySubtopic: false
            }
            ListElement {
                myNameTopic: "ООП, ФП, АУЕ"
                //pathTopicIcon: "../../../../YandexDisk/RushPolytech/icons/automatic.png"
                mySubtopic: true
            }
        }
        delegate: Topic {

            subtopic: mySubtopic
            nameTopic: myNameTopic
            pathTopicIcon: myPathTopicIcon

            anchors.left: parent.left
            anchors.right: parent.right
            height: listView.height / 7
        }
        currentIndex: 1

        //нада шоб при увеличении экрана отражалось больше текста
    }
}
