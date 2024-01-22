import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import injector
import presenters

QmlInjector {
    property string walletId: ""

    implicitWidth: view ? view.width: 0
    implicitHeight: view ? view.height : 0

    sourceComponent: ColumnLayout {
        width: 150

        property WalletListModel $model
        property Item injector

        component Delegate: Item {

            property alias name: nameText.text
            property alias amount: amountText.text
            property alias selected: bg.visible

            signal itemSelected

            width: parent ? parent.width : 0
            height: row.height
            Rectangle {
                id: bg
                anchors.fill: row
                border.width: 1
                border.color: "gray"
                color: "transparent"
            }
            RowLayout {
                id: row
                spacing: 10
                width: parent ? parent.width : 0
                Text {
                    id: nameText
                    font.bold: true
                    color: "white"
                    Layout.fillWidth: true
                }
                Text {
                    id: amountText
                    font.bold: false
                    color: "white"
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    itemSelected();
                }
            }
        }

        ListView {
            spacing: 2
            width: 150
            height: contentHeight

            Binding {
                target: injector
                property: "walletId"
                value: $model.selectedWalletId
            }

            model: $model

            delegate: Delegate {
                selected: model.roleSelected
                name: model.roleName
                amount: model.roleAmount
                onItemSelected: {
                    model.roleSelected = !model.roleSelected;
                }
            }
        }
    }
}

