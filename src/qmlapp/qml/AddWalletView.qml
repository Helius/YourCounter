import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import injector
import presenters

import "Controls"

Popup {
    id: popup
    padding: 30
    modal: true
    focus: true
    anchors.centerIn: parent
    signal closePopup
    QmlInjector {
        implicitWidth: view ? view.width : 0
        implicitHeight: 300

        function close() {
            popup.close();
            popup.parent.active = false;
        }

        sourceComponent: ColumnLayout {
            property AddNewWalletPresenter $presenter
            property Item injector

            Connections {
                target: $presenter
                function onClose() {
                    injector.close();
                }
            }

            NamedField {
                id: name
                name: "Name"
                edit.cursorVisible: true
                edit.focus: true
                Binding {
                    target: $presenter.vm
                    property: "name"
                    value: name.edit.text
                    //                        when: priv.enabled
                }
            }

            NamedField {
                id: amount
                name: "Amount"
                edit.cursorVisible: true
                edit.focus: true
                edit.validator: $presenter.vm.amountValidator
                Binding {
                    target: $presenter.vm
                    property: "initAmount"
                    value: amount.edit.text
                    //                        when: priv.enabled
                }
            }

            SButton {
                Layout.alignment: Qt.AlignCenter
                text: "Add"
                onClicked: {
                    $presenter.add()
                }
            }
        }
    }
}
