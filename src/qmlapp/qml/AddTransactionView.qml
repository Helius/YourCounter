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
        property AddTransactionButtonPresenter $presenter
        property Item injector

        Connections {
            target: $presenter
            function onAskAboutNewCategory() {
                dialog.open()
            }
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
            edit.validator: $presenter.amountValidator
            Binding {
                target: $presenter
                property: "amount"
                value: amount.edit.text
            }
        }
        NamedField {
            id: cat
            name: "Caterogy"
            Binding {
                target: $presenter
                property: "category"
                value: cat.edit.text
            }
        }
        NamedField {
            id: coment
            name: "Coment"
            Binding {
                target: $presenter
                property: "coment"
                value: coment.edit.text
            }
        }
        NamedField {
            id: who
            name: "Who"
            edit.text: "pc"
            Binding {
                target: $presenter
                property: "who"
                value: who.edit.text
            }
        }
        SButton {
            Layout.alignment: Qt.AlignCenter
            text: "Done"
            onClicked: {
                $presenter.add()
            }
        }
        Keys.onReturnPressed: {
            $presenter.add()
        }

        Dialog {
            id: dialog
            title: "Add new category: " + $presenter.category
            standardButtons: Dialog.Ok | Dialog.Cancel
            modal: true
            onAccepted: {
                $presenter.add(true)
            }
            onRejected: {
                console.log("Cancel clicked")
            }
        }
    }
}
