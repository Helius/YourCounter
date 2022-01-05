import QtQuick 2.0
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

        // group list
        ListView {
            model: $groupModel
            Rectangle {
                anchors.fill: parent
                border.width: 1
                border.color: "green"
                color: "transparent"
            }
            Layout.fillHeight: true
            Layout.preferredWidth: 300
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
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
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
                border.color: "red"
                color: "transparent"
            }
            model: $transactionModel
            Layout.fillHeight: true
            Layout.fillWidth: true

            delegate: Item {
                width: 200
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
                            text: model.category
                            color: "white"
                            font.pointSize: 12
                        }
                        AmountCell {
                            amount: model.amount
                            background: Material.backgroundDimColor
                        }
                    }
                    Text {
                        text: model.date + " by " + model.who
                        font.pointSize: 8
                        font.weight: Font.Light
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

            RoundButton {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: "Add transaction"
                onClicked: {
                    addTransactionPopup.open()
                }
            }
        }
    }
}
