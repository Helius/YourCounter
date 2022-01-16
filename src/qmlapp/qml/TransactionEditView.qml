import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import "Controls"

ColumnLayout {
    id: root
    property var vm
    spacing: 20

    Component.onCompleted: {
        categorySuggester.setCategoryId(vm.categoryId);
    }

    NamedField {
        id: amount
        name: "Amount"
        edit.cursorVisible: true
        edit.focus: true
        edit.validator: vm.amountValidator
        Binding {
            target: vm
            property: "amount"
            value: amount.edit.text
        }
    }
    CategorySuggester {
        id: categorySuggester
        Layout.preferredWidth: implicitWidth
        Layout.preferredHeight: implicitHeight
        Binding {
            target: vm
            property: "categoryId"
            value: categorySuggester.categoryId
        }
    }
    DatePicker {
        id: datePicker
        Layout.preferredWidth: 300
        Layout.preferredHeight: 180
        onClicked: date => {
                       vm.when = date;
                   }
    }
    NamedField {
        id: comment
        name: "Comment"
        Binding {
            target: vm
            property: "comment"
            value: comment.edit.text
        }
    }
    NamedField {
        id: who
        name: "Who"
        Binding {
            target: vm
            property: "who"
            value: who.edit.text
        }
    }
}
