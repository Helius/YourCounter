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
                border.color: "gray"
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
                border.color: "gray"
                color: "transparent"
            }
            model: $transactionModel
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 4

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
                        spacing: 10
                        Text {
                            text: model.categoryName
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
                            amount: model.amount
                            background: "transparent"
                        }
                    }
                    Text {
                        text: model.date + " by " + model.who
                        font.pointSize: 10
                        font.weight: Font.Light
                        color: "gray"
                    }
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
                anchors.right: parent.right
                text: "Add transaction"
                onClicked: {
                    addTransactionPopup.open()
                }
            }
        }
    }
}
