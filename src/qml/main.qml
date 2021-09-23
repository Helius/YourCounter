import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import presenters
import injector
import Models 1.0 as Models
import "Controls"

ApplicationWindow {
    //    menuBar: MenuBar {
    //        Menu {
    //            title: qsTr("Menu")
    //            Action { text: qsTr("&New...") }
    //            Action { text: qsTr("&Open...") }
    //            Action { text: qsTr("&Save") }
    //            Action { text: qsTr("Save &As...") }
    //            MenuSeparator { }
    //            Action { text: qsTr("&Quit") }
    //        }
    //    }

    visibility: "Maximized"
    visible: true
    title: qsTr("Your Counter")
    Material.theme: Material.Dark

    Component {
    id: mainComponent

         Item {

            HorizontalHeaderView {
                id: hHeader

                anchors.left: vHeader.right
                width: tableView.width
                syncView: tableView
            }

            VerticalHeaderView {
                id: vHeader

                anchors.top: tableView.top
                height: tableView.height
                syncView: tableView
            }

            TableView {
                id: tableView

                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: hHeader.bottom
                anchors.left: vHeader.right
                rowSpacing: 1
                columnSpacing: 1
                model: Models.TimeTable
                columnWidthProvider: Models.TimeTable.getColumnWidth

                ScrollBar.vertical: ScrollBar {
                    visible: true
                }

                delegate: AmountCell {
                    amount: model.amount
                    background: model.color
                    current: model.isCurrent
                }

            }

        }


    }

    Timer {
        id: timer

        interval: 300
        Component.onCompleted: timer.running = true
        onTriggered: {
            mainStack.push(mainComponent);
        }
    }

    StackView {
        id: mainStack

        anchors.fill: parent

        initialItem: Item {
            BusyIndicator {
                anchors.centerIn: parent
                width: 60
                height: 60
                running: true
            }
        }
    }

    header: Rectangle {
        color: Material.backgroundDimColor
        height: buttonRow.height
        width: parent.width

        HeaderButtonRow {
            id: buttonRow
            width: parent.width
        }
    }

    footer: Rectangle {
        color: Material.backgroundDimColor
        height: 10
    }

}
