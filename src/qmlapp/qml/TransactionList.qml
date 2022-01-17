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
            z:3
            width: parent.width
            sourceComponent: Rectangle {
                color: "gray"
                anchors.fill: parent

                property CurentBalancePresenter $presenter
                Text {
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
