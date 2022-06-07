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
            Layout.preferredWidth: 180
            Layout.fillHeight: true
            model: $groupModel
        }

        // transaction list
        TransactionList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: $transactionModel
        }

        // current month report
        CurrentMonthSummary {
            Layout.fillHeight: true
            Layout.preferredWidth: 250
            model: $monthReportModel
        }
    }
}
