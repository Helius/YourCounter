import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

QmlInjector {
    id: root
    signal closePopup
    signal init(var data)
    implicitWidth: view ? view.width : 0
    implicitHeight: view ? view.height : 0


    sourceComponent: Item {
        height: col.implicitHeight
        width: col.implicitWidth
        property AddTransactionPresenter $presenter
        property Item injector

        Connections {
            target: parent
            function onInit(data) {
                editView.init();
                $presenter.initWithData(data)
            }
        }

        Connections {
            target: $presenter
            function onClosePopup() {
                injector.closePopup()
            }
        }
        ColumnLayout {
            id: col
            spacing: 8

            TransactionEditView {
                id: editView
                vm: $presenter.vm
            }
            SButton {
                Layout.alignment: Qt.AlignCenter
                text: "Done"
                onClicked: {
                    $presenter.apply()
                }
            }
        }
        Keys.onReturnPressed: {
            $presenter.apply()
        }
    }
}
