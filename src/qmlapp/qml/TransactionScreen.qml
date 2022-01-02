import QtQuick 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

QmlInjector {
    id: root
    sourceComponent:
        ListView {

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
            text: "Add"
            onClicked: {
                addTransactionPopup.open();
            }
        }

        anchors.fill: parent
        property TransactionSortedListModel $transactionModel
        model: $transactionModel
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
    }
}