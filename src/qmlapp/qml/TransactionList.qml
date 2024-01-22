import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

ColumnLayout {
    property alias model: list.model

    WalletHorisontalList {
        id: walletList
        Layout.fillWidth: true
        onCurrentWalletIdChanged:  {
            model.currentWalletId = walletList.currentWalletId;
            list.positionViewAtEnd();
        }
    }

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
        spacing: 2
        clip: true
        Component.onCompleted: {
            list.positionViewAtEnd();
        }
        property bool scrolled: !atYEnd
        onContentYChanged: {
            scrolled = !atYEnd
        }
        onFlickEnded: {
            scrolled = !atYEnd
        }

        headerPositioning: ListView.OverlayHeader
        footerPositioning: ListView.OverlayFooter
        footer: Pane {
            visible: model.selectedAmount || list.scrolled
            height: 30
            z: 2
            width: parent.width
            Row {
                id: footerRow
                anchors.top: parent ? parent.top : undefined
                anchors.right: parent ? parent.right : undefined
                anchors.rightMargin: 20
                spacing: 10
                Text {
                    verticalAlignment: Text.AlignVCenter
                    color: "gray"
                    text: model.selectedAmount
                }
                RoundButton {
                    anchors.top: parent.top
                    anchors.topMargin: -10
                    width: 100
                    height: 30
                    text: "Down"
                    visible: list.scrolled
                    onClicked: {
                        list.positionViewAtEnd()
                    }
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
                font.weight: Font.Light
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
                    console.log("transactionId: ", model.transactionId, "walletName:", model.walletName, "categoryName:")
                }
            }
            ColumnLayout {
                id: col

                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 10
                    rightMargin: 10
                }
                RowLayout {
                    width: parent.width
                    spacing: 12
                    Text {
                        text: model.categoryName
                        Layout.preferredWidth: implicitWidth
                        color: "white"
                        font.pointSize: 12
                        font.weight: Font.Light
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
                RowLayout {
                    Layout.topMargin: -6
                    Layout.fillWidth: true
                    Text {
                        text: model.walletName
                        font.pointSize: 9
                        font.weight: Font.Light
                        color: "gray"
                    }
                    Rectangle {
                        width: visible ? 6 : 0
                        height: 6
                        radius: 3
                        color: "gray"
                        visible: model.walletName && model.who
                    }
                    Text {
                        text: model.who
                        font.pointSize: 9
                        font.weight: Font.Light
                        color: "gray"
                    }
                    Item {
                        height: 1
                        Layout.fillWidth: true

                    }
                    Text {
                        Layout.alignment: Qt.AlignRight
                        text: model.totalBy
                        font.pointSize: 9
                        font.weight: Font.Light
                        color: "gray"
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
            id: transferPopupLoader
            active: false
            sourceComponent: AddTransferPopup {
                id: transferPopup
                anchors.centerIn: parent
                closePolicy: Popup.CloseOnEscape
                focus: true
                modal: true
            }
            onLoaded: {
                item.open()
            }
        }


        Loader {
            id: editPopupLoader
            onLoaded: {
                item.open()
            }
        }
        DropArea {
            anchors.fill: parent
            onDropped: {
                console.log("helius: drop text", drop.text)
                addTransactionPopup.open()
                addTransactionPopup.init(drop.text)
            }
        }
    }

    RowLayout {
            Layout.alignment: Qt.AlignCenter
        RoundButton {
            text: "Add transaction"
            onClicked: {
                addTransactionPopup.open()
            }
        }
        RoundButton {
            text: "Transfer"
            onClicked: {
                transferPopupLoader.active = true;
            }
        }
    }

}
