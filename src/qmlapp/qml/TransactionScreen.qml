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
        GroupCategoryList {
            Layout.fillHeight: true
            Layout.preferredWidth: 250
            model: $groupModel
        }

        // transaction list
        TransactionList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: $transactionModel
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
            Layout.preferredWidth: 300
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
