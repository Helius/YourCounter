import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import "Controls"

ColumnLayout {
    id: root
    property var vm
    spacing: 20

    function init() {
        comment.edit.text = "";
        amount.edit.text = "";
    }

    QtObject {
        id: priv
        property bool enabled: false
    }

    Component.onCompleted: {
        categorySuggester.categoryText = vm.category;
        datePicker.set(vm.when);
        comment.edit.text = vm.comment;
        amount.edit.text = vm.amount;
        who.edit.text = vm.who || "pc";

        priv.enabled = true;
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
            when: priv.enabled
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
            when: priv.enabled
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

    WalletSelector {
        id: walletSelector
        Binding {
            target: vm
            property: "walletId"
            value: walletSelector.walletId
            when: priv.enabled
        }
    }

    NamedField {
        id: comment
        name: "Comment"
        Binding {
            target: vm
            property: "comment"
            value: comment.edit.text
            when: priv.enabled
        }
    }
    NamedField {
        id: who
        name: "Who"
        Binding {
            target: vm
            property: "who"
            value: who.edit.text
            when: priv.enabled
        }
    }
}
