import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import Models 1.0 as Models

ApplicationWindow {
    visibility: "Maximized"
    visible: true
    title: qsTr("Your Counter")
    Material.theme: Material.Dark

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
                anchors.top:tableView.top
                height: tableView.height
                syncView: tableView
            }
            TableView {
                id: tableView
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: hHeader.bottom
                anchors.left: vHeader.right
                rowSpacing: 2
                columnSpacing: 2
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
        onTriggered: {
            mainStack.push(mainComponent)
        }
        Component.onCompleted: timer.running = true
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
        Row {
            id: buttonRow
            SButton {
                text: "Year"
            }
            SButton {
                text: "Month"
            }
            SButton {
                text: "Week"
            }
            SButton {
                text: "Days"
            }
        }
    }

    footer: Rectangle {
        color: Material.backgroundDimColor
        height: 10
    }

}
