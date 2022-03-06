import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

ColumnLayout {
    property alias model: list.model
    ListView {
        id: list
        Layout.fillHeight: true
        Layout.fillWidth: true
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "gray"
            color: "transparent"
        }
        spacing: 4
        clip: true

        headerPositioning: ListView.OverlayHeader
        header: QmlInjector {
            height: 40
            z: 3
            width: parent.width
            sourceComponent: Rectangle {
                color: "gray"
                anchors.fill: parent

                property CurentBalancePresenter $presenter
                RowLayout {
                    anchors {
                        left: parent ? parent.left : undefined
                        leftMargin: 10
                        top: parent ? parent.top : undefined
                        topMargin: 6
                    }
                    spacing: 16

                    Text {
                        font.pointSize: 14
                        color: "white"
                        text: "Balance: " + $presenter.currentBalance
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 0
                        Text {
                            font.pointSize: 10
                            color: "white"
                            text: "Earn: " + $presenter.earn
                        }
                        Text {
                            font.pointSize: 10
                            color: "white"
                            text: "Spend: " + $presenter.spend
                        }
                    }
                }
            }
        }
        footer: Item {
            visible: model.selectedAmount
            height: 30
            width: parent.width
            Text {
                anchors.right: parent ? parent.right : undefined
                anchors.rightMargin: 20
                verticalAlignment: Text.AlignVCenter
                color: "gray"
                text: model.selectedAmount
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
        delegate: Rectangle {
            width: ListView.view.width
            height: col.implicitHeight
            color: "transparent"
            border.width: model.selected ? 1 : 0
            border.color: "gray"

            MouseArea {
                anchors.fill: col
                onClicked: {
                    model.selected = !model.selected
                }
            }
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
                        editPopupLoader.setSource(
                                    "qrc:/qml/EditTransactionPopup.qml", {
                                        "transactionId": model.transactionId
                                    })
                    }
                }
            }
            HoverHandler {
                id: hoverHandler
            }
        }

        AddTransactionPopup {
            id: addTransactionPopup
            modal: true
            focus: true
            anchors.centerIn: parent
            closePolicy: Popup.CloseOnEscape
        }

        Loader {
            id: editPopupLoader
            onLoaded: {
                item.open()
            }
        }
    }

    RoundButton {
        Layout.alignment: Qt.AlignCenter
        text: "Add transaction"
        onClicked: {
            addTransactionPopup.open()
        }
    }
}
