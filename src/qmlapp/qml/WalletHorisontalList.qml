import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import injector
import presenters

QmlInjector {

    property string currentWalletId: ""

    implicitHeight: view ? view.implicitHeight : 0

    sourceComponent: Item {

        property WalletListModel $model
        property Item injector


        implicitHeight: flow.height
        width: parent ? parent.width : undefined

        Connections {
            target: $model
            function onSelectedWalletIdChanged() {
                injector.currentWalletId = $model.selectedWalletId;
            }
        }

        function showAddWalletPopup() {
            popUpLoader.active = true;
        }


        Loader {
            id: popUpLoader
            active: false
            sourceComponent: AddWalletView {
            }
            onLoaded: {
                item.open()
            }
        }

        component WalletDelegate:
            Rectangle {
            id: root
            property alias name: name.text
            property alias amount: amount.text
            property bool selected: false
            property bool showBorder: true
            property alias icon: image.source

            signal clicked

            width: 80
            height: 80
            color: "transparent"
            Rectangle {
                anchors.fill: parent
                anchors.margins: 4
                border.width: 1
                color: hh.hovered ? Material.primary : "transparent"
                border.color: selected
                              ? Material.accent
                              : (showBorder ? "gray" : "transparent")
                radius: 8
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 6
                    Text {
                        id: name
                        color: "white"
                        font.pointSize: 14
                        font.weight: Font.Light
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Text {
                        id: amount
                        color: "white"
                        font.pointSize: 10
                        font.weight: Font.Medium
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                    }
                }
            }
            Image {
                id: image
                width: 32
                height: 32
                anchors.top: amount.text ? parent.top : undefined
                anchors.topMargin: amount.text ? 10 : undefined
                anchors.verticalCenter: amount.text ? undefined : parent.verticalCenter
                anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
                sourceSize {
                    width: 32
                    height: width
                }
            }
            HoverHandler {
                id: hh
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked();
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "gray"
            color: "transparent"
        }

        Flow {
            id: flow
            width: parent ? parent.width : 0
            anchors.margins: 8
            spacing: 0
            WalletDelegate {
                selected: !$model.selectedWalletId
                showBorder: false
                icon: "qrc:/qml/icons/all_inbox_white_24dp.svg"
                amount: $model.defaultWalletTotal
                onClicked: {
                    $model.clearSelection();
                }
            }
            Repeater {
                model: $model
                delegate: WalletDelegate {
                    selected: model.roleSelected
                    name: model.roleName
                    amount: model.roleAmount
                    onClicked: {
                        model.roleSelected = !model.roleSelected
                    }
                }
            }
            WalletDelegate {
                showBorder: false
                icon: "qrc:/qml/icons/control_point_white_24dp.svg"
                onClicked: {
                    showAddWalletPopup();
                }
            }
        }
    }
}
