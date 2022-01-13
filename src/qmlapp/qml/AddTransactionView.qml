import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

QmlInjector {
    id: root
    signal closePopup
    sourceComponent: ColumnLayout {
        property AddTransactionPresenter $presenter
        property Item injector

        Connections {
            target: $presenter
            function onClosePopup() {
                injector.closePopup()
            }
        }

        width: parent.width
        spacing: 20

        NamedField {
            id: amount
            name: "Amount"
            edit.cursorVisible: true
            edit.focus: true
            edit.validator: $presenter.vm.amountValidator
            Binding {
                target: $presenter.vm
                property: "amount"
                value: amount.edit.text
            }
        }
        CategorySuggester {
            id: categorySuggester
            Layout.preferredWidth: implicitWidth
            Layout.preferredHeight: implicitHeight
            onSetCategoryId: id => {
                $presenter.vm.categoryId = id;
            }
        }
        DatePicker {
            id: datePicker
            Layout.preferredWidth: 300
            Layout.preferredHeight: 180
            onClicked: date => {
                $presenter.vm.when = date;
            }
        }
        NamedField {
            id: coment
            name: "Coment"
            Binding {
                target: $presenter.vm
                property: "coment"
                value: coment.edit.text
            }
        }
        NamedField {
            id: who
            name: "Who"
            edit.text: "pc"
            Binding {
                target: $presenter.vm
                property: "who"
                value: who.edit.text
            }
        }
        SButton {
            Layout.alignment: Qt.AlignCenter
            text: "Done"
            onClicked: {
                $presenter.apply()
            }
        }
        Keys.onReturnPressed: {
            $presenter.apply()
        }
    }
}
