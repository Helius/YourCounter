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
            edit.validator: $presenter.amountValidator
            Binding {
                target: $presenter
                property: "amount"
                value: amount.edit.text
            }
        }
        CategorySuggester {
            id: categorySuggester
            Layout.preferredWidth: implicitWidth
            Layout.preferredHeight: implicitHeight
            onSetCategoryId: id => {
                console.log("helius: categoryId is:", id);
                $presenter.categoryId = id;
            }
        }
        DatePicker {
            id: datePicker
            Layout.preferredWidth: 300
            Layout.preferredHeight: 180
            onClicked: date => {
                console.log("helius: date is:", date);
                $presenter.when = date;
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
