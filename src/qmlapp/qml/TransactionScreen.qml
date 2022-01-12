import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

QmlInjector {
    id: root
    sourceComponent: RowLayout {

        anchors.fill: parent
        property TransactionSortedListModel $transactionModel
        property GroupListModel $groupModel
        property MonthReportSortedModel $monthReportModel

        // group list
        ListView {
            model: $groupModel
            Rectangle {
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
                color: "transparent"
            }
            clip: true
            Layout.fillHeight: true
            Layout.preferredWidth: 250
            delegate: GroupCategoryDelegate {
                groupId: model.groupId
                groupName: model.groupName
            }

            AddNewGroupPopup {
                id: newGroupPopup
                width: 400
                height: 400
                modal: true
                focus: true
                anchors.centerIn: parent
                closePolicy: Popup.CloseOnEscape
            }
            AddNewCategoryPopup {
                id: newCategoryPopup
                width: 400
                height: 400
                modal: true
                focus: true
                anchors.centerIn: parent
                closePolicy: Popup.CloseOnEscape
            }

            RowLayout {
                anchors.bottom: parent ? parent.bottom : undefined
                anchors.right: parent ? parent.right : undefined
                RoundButton {
                    text: "Add Group"
                    onClicked: {
                        newGroupPopup.open()
                    }
                }
                RoundButton {
                    text: "Add Category"
                    onClicked: {
                        newCategoryPopup.open()
                    }
                }
            }
        }

        // transaction list
        ListView {
            Rectangle {
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
                color: "transparent"
            }
            model: $transactionModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 4
            clip: true

            headerPositioning: ListView.OverlayHeader
            header: QmlInjector {
                height: 40
                sourceComponent: Text {
                    property CurentBalancePresenter $presenter
                    anchors {
                        left: parent ? parent.left : undefined
                        leftMargin: 10
                        top: parent ? parent.top : undefined
                        topMargin: 10
                    }
                    font.pointSize: 14
                    color: "white"
                    text: "Current balance: " + $presenter.currentBalance
                }
            }
            section.property: "date"
            section.criteria: ViewSection.FullString
            section.delegate: Item {
                required property string section
                width: ListView.view.width
                height: 20
                Text {
                    width: parent ? parent.width : 0
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: section
                    color: "gray"
                }
            }
            delegate: Item {
                width: ListView.view.width
                height: col.implicitHeight
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
                        spacing: 4
                        Text {
                            text: model.who
                            font.pointSize: 8
                            font.weight: Font.Light
                            color: "gray"
                        }
                        Text {
                            text: model.categoryName
                            Layout.preferredWidth: implicitWidth
                            color: "white"
                            font.pointSize: 12
                        }
                        Text {
                            Layout.fillWidth: true
                            visible: text
                            text: model.comment
                            font.pointSize: 10
                            font.weight: Font.Light
                            color: "white"
                        }
                        AmountCell {
                            Layout.alignment: Qt.AlignRight
                            Layout.fillWidth: true
                            amount: model.amount
                            background: "transparent"
                        }
                    }
                }
                Rectangle {
                    width: editButton.width
                    height: editButton.height
                    color: "gray"
                    visible: hoverHandler.hovered
                    radius: 2
                    anchors {
                        right: parent.right
                        rightMargin: 8
                    }
                    Image {
                        id: editButton
                        source: "qrc:/qml/icons/edit_white_24dp.svg"
                        width: 18
                        height: width
                        sourceSize {
                            width: 18
                            height: width
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("helius: edit ", model.transactionId)
                        }
                    }
                }
                HoverHandler {
                    id: hoverHandler
                }
            }

            AddTransactionPopup {
                id: addTransactionPopup
                width: 400
                height: 600
                modal: true
                focus: true
                anchors.centerIn: parent
                closePolicy: Popup.CloseOnEscape
            }

            RoundButton {
                anchors.bottom: parent ? parent.bottom : undefined
                anchors.right: parent ? parent.right : undefined
                text: "Add transaction"
                onClicked: {
                    addTransactionPopup.open()
                }
            }
        }

        // current month report
        ListView {
            model: $monthReportModel
            Rectangle {
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
                color: "transparent"
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 4
            clip: true
            section.property: "groupName"
            section.criteria: ViewSection.FullString
            section.delegate: Item {
                required property string section
                width: ListView.view.width
                Text {
                    anchors {
                        left: parent ? parent.left : undefined
                        leftMargin: 10
                    }
                    text: section
                    color: "white"
                    font.bold: true
                }
                height: 16
            }
            delegate: Item {
                width: ListView.view.width
                height: 20
                RowLayout {
                    id: rowLayout
                    anchors {
                        left: parent.left
                        right: parent.right
                        leftMargin: 20
                        rightMargin: 10
                    }
                    Text {
                        text: model.categoryName
                        color: "white"
                    }
                    AmountCell {
                        Layout.alignment: Qt.AlignRight
                        amount: model.totalAmount
                        background: "transparent"
                    }
                }
            }
        }
    }
}
