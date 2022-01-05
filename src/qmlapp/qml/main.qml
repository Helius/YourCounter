import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
//import Models as Models
//import presenters
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
    width: 1000
    height: 1000
    //visibility: "Maximized"
    visible: true
    title: qsTr("Your Counter")
    Material.theme: Material.Dark

    //    Component {
    //        id: mainComponent
    //        RowLayout {

    //            Item {
    //                Layout.fillWidth: true
    //                Layout.fillHeight: true

    //                HorizontalHeaderView {
    //                    id: hHeader

    //                    anchors.left: vHeader.right
    //                    width: tableView.width
    //                    clip: true
    //                    syncView: tableView
    //                }

    //                VerticalHeaderView {
    //                    id: vHeader

    //                    anchors.top: tableView.top
    //                    height: tableView.height
    //                    clip: true
    //                    syncView: tableView
    //                }

    //                TableView {
    //                    id: tableView

    //                    anchors.right: parent.right
    //                    anchors.bottom: parent.bottom
    //                    anchors.top: hHeader.bottom
    //                    anchors.left: vHeader.right
    //                    clip: true
    //                    rowSpacing: 1
    //                    columnSpacing: 1
    //                    model: Models.TimeTable
    //                    columnWidthProvider: Models.TimeTable.getColumnWidth

    //                    ScrollBar.vertical: ScrollBar {
    //                        visible: true
    //                    }

    //                    delegate: AmountCell {
    //                        amount: model.amount
    //                        background: model.color
    //                        current: model.isCurrent
    //                    }
    //                }
    //            }
    //            Rectangle {
    //                width: 200
    //                height: parent.height
    //                color: Material.backgroundDimColor

    //                QmlInjector {
    //                    anchors.fill: parent

    //                    function addTransaction() {
    //                        addTransactionPopup.open()
    //                    }

    //                    sourceComponent: ColumnLayout {

    //                        property TransactionSortedListModel $transactionModel

    //                        property Item injector
    //                        anchors.fill: parent
    //                        spacing: 10
    //                        ListView {
    //                            width: parent.width
    //                            Layout.fillHeight: true
    //                            model: $transactionModel
    //                            spacing: 3
    //                            delegate: Item {
    //                                width: 200
    //                                height: col.height
    //                                Column {
    //                                    id: col
    //                                    anchors {
    //                                        left: parent.left
    //                                        right: parent.right
    //                                        leftMargin: 10
    //                                        rightMargin: 10
    //                                    }
    //                                    RowLayout {
    //                                        width: parent.width
    //                                        Text {
    //                                            Layout.fillWidth: true
    //                                            text: model.category
    //                                            color: "white"
    //                                            font.pointSize: 12
    //                                        }
    //                                        AmountCell {
    //                                            amount: model.amount
    //                                            background: Material.backgroundDimColor
    //                                        }
    //                                    }
    //                                    Text {
    //                                        text: model.date + " by " + model.who
    //                                        font.pointSize: 8
    //                                        font.weight: Font.Light
    //                                    }
    //                                }
    //                            }
    //                        }
    //                        SButton {
    //                            Layout.alignment: Qt.AlignHCenter
    //                            text: "Add"
    //                            onClicked: injector.addTransaction()
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //    AddTransactionPopup {
    //        id: addTransactionPopup
    //        width: 400
    //        height: 400
    //        modal: true
    //        focus: true
    //        anchors.centerIn: parent
    //        closePolicy: Popup.CloseOnEscape
    //    }

    //    Timer {
    //        id: timer

    //        interval: 300
    //        Component.onCompleted: timer.running = true
    //        onTriggered: {
    //            mainStack.push(mainComponent)
    //        }
    //    }
    RowLayout {
        anchors.fill: parent
        spacing: 8
        anchors.margins: 8

        // navbar
        Rectangle {
            border.width: 1
            border.color: "gray"
            color: "transparent"

            Layout.preferredWidth: image.width
            Layout.preferredHeight: parent.height

            Image {
                id: image
                anchors.top: parent.top
                width: 36
                height: width
                sourceSize {
                    width: 36
                    height: width
                }
                source: "qrc:/qml/icons/settings_white_24dp.svg"
            }
        }

        // screen stack
        StackView {
            id: mainStack
            Layout.fillHeight: true
            Layout.fillWidth: true
            initialItem: StartUpScreen {
                onStartUpFinished: {
                    mainStack.push("qrc:/qml/TransactionScreen.qml")
                }
            }
        }
    }
}
