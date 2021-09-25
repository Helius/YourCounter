import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

QmlInjector {
    sourceComponent: ColumnLayout {
        property AddTransactionButtonPresenter $presenter

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
    }
}
