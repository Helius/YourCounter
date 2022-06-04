import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

Popup {
    id: popup
    padding: 30
    QmlInjector {
        implicitWidth: view ? view.width : 0
        implicitHeight: view ? view.height: 0

        function close() {
            popup.close();
            popup.parent.active = false;
        }

        sourceComponent: ColumnLayout {
            property NewTransferPresenter $presenter
            property Item injector

            RowLayout {
                spacing: 8

                WalletSelector {
                    id: sourceWallet
                    Binding{
                        target: $presenter
                        property: "srcWallet"
                        value: sourceWallet.walletId
                    }
                }
                WalletSelector {
                    id: destWallet
                    Binding{
                        target: $presenter
                        property: "dstWallet"
                        value: destWallet.walletId
                    }
                }
            }

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
            SButton {
                Layout.alignment: Qt.AlignCenter
                text: "Add"
                active: (sourceWallet.walletid !== destWallet.walletId) && !!amount.edit.text
                onClicked: {
                    if($presenter.add()) {
                        injector.close();
                    }
                }
            }

        }
    }
}