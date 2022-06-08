import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

ColumnLayout {
    id: root
    property alias model: list.model

    ColumnLayout {
        Text {
            color: "white"
            font.weight: Font.Light
            text: "Earn: " + root.model.earn
        }
        Text {
            color: "white"
            font.weight: Font.Light
            text: "Spend: " + root.model.spend
        }
        Text {
            color: "white"
            font.weight: Font.Light
            text: "Diff: " + root.model.diff
        }
    }

    ListView {
        id: monthList
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 20
        orientation: Qt.Horizontal
        model: ["Янв", "Фев", "Мар", "Апр", "Май", "Июн", "Июл", "Авг", "Сен", "Окт", "Ноя", "Дек"]
        spacing: 6
        delegate: Text {
            property bool selected: (index + 1) === root.model.monthIndex
            text: modelData
            color: selected ? Material.accent : "white"
            font.bold: selected
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.model.monthIndex = index + 1;
                }
            }
        }
    }

    ListView {
        id: list
        Layout.preferredWidth: parent.width
        Layout.fillHeight: true
        Layout.topMargin: 10
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "#938F99"
            color: "transparent"
        }
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
            Rectangle {
                anchors.fill: rowLayout
                border.width: 1
                border.color: "gray"
                color: "transparent"
                visible: model.selected
            }
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
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    model.selected = !model.selected;
                }
            }
        }
    }
}
