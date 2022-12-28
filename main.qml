import QtQuick
import QtQuick.Controls

ApplicationWindow {

    width: 420
    height: 736

    visible: true
    title: qsTr("Hello World")

    header: MyHeader{

    }
        StackView {
            id: view
            anchors.fill: parent

            Page {
                title: qsTr("Home")
            }
            Page {
                title: qsTr("Discover")
            }
            Page {
                title: qsTr("Activity")
            }
        }
}
