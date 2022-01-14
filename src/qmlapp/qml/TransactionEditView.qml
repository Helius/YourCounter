import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import "Controls"

ColumnLayout {
    id: col
    property var vm
    spacing: 20

    Component.onCompleted: {
        amount.edit.text = vm.amount
        categorySuggester
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
        onCategoryIdSelected: id => {
                             vm.categoryId = id;
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
        id: coment
        name: "Coment"
        Binding {
            target: vm
            property: "coment"
            value: coment.edit.text
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
