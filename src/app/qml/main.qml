import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import Models as Models
import presenters
import injector

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
        RowLayout {

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                HorizontalHeaderView {
                    id: hHeader

                    anchors.left: vHeader.right
                    width: tableView.width
                    clip: true
                    syncView: tableView
                }

                VerticalHeaderView {
                    id: vHeader

                    anchors.top: tableView.top
                    height: tableView.height
                    clip: true
                    syncView: tableView
                }

                TableView {
                    id: tableView

                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: hHeader.bottom
                    anchors.left: vHeader.right
                    clip: true
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
            Rectangle {
                width: 200
                height: parent.height
                color: Material.backgroundDimColor
                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10
                    ListView {
                        width: parent.width
                        Layout.fillHeight: true
                        model: 6
                        spacing: 3
                        delegate: Item {
                            width: parent.width
                            height: col.height
                            Column {
                                id: col
                                anchors {
                                    left: parent.left
                                    right: parent.right
                                    leftMargin: 10
                                    rightMargin: 10
                                }
                                RowLayout {
                                    width: parent.width
                                    Text {
                                        Layout.fillWidth: true
                                        text: "Английский"
                                        color: "white"
                                        font.pointSize: 12
                                    }
                                    AmountCell {
                                        amount: "-6794"
                                        background: Material.backgroundDimColor
                                    }
                                }
                                Text {
                                    text: "24 Сентября 2021 by Alexandra"
                                    font.pointSize: 8
                                    font.weight: Font.Light
                                }
                            }
                        }
                    }
                    SButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Add"
                        onClicked: addTransactionPopup.open()
                    }
                }
            }
        }
    }
    AddTransactionPopup {
        id: addTransactionPopup
        width: 400
        height: 400
        modal: true
        focus: true
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape
    }

    Timer {
        id: timer

        interval: 300
        Component.onCompleted: timer.running = true
        onTriggered: {
            mainStack.push(mainComponent)
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
