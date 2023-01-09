import QtQuick
import QtQuick.Controls

ApplicationWindow {

    width: 420
    height: 736

    visible: true
    title: qsTr("Hello World")

    header: MyHeader{
        id: myAppHeader
        x:0
        y:0
        anchors.left: parent.left
        anchors.right: parent.right


        height: parent.height /12

        onBurgerButtonClicked: {
            if(drawer.opened)
                drawer.close();
            else
                drawer.open();
        }
    }


    StackView {
        id: view
        anchors.top: myAppHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right

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


    Drawer {
        id: drawer
        y: myAppHeader.height
        width: parent.width * 0.4
        height: parent.height
        //visible: (stackView.currentItem.title === "Соединение с Moodle")||(stackView.currentItem.title === "Авторизация с Moodle")||(stackView.currentItem.title === "Загрузка данных")

        Column {
            anchors.fill: parent

            ItemDelegate {
                width: parent.width
                height: parent.height/14

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "На главную"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Учить"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14

                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Повторить"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Экзамен"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Теория"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Статистика"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Настройки"

                    onClicked: {
                        drawer.close()
                    }
                }
            }

            ItemDelegate {
                width: parent.width
                height: parent.height/14
                ItemOfDrawer{
                    anchors.fill: parent
                    textOfItem: "Выход"

                    onClicked: {
                        drawer.close()
                    }
                }
            }
        }//endcolumn
    }//end drawer

}//end window
