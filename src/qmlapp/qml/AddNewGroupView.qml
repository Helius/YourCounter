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

        property AddGroupPresenter $presenter
        property Item injector

        Connections {
            target: $presenter
            function onClosePopup() {
                injector.closePopup()
            }
        }

        NamedField {
            id: name
            name: "Group name"
            Binding {
                target: $presenter
                property: "name"
                value: name.edit.text
            }
        }

        SButton {
            Layout.alignment: Qt.AlignCenter
            text: "Create group"
            onClicked: {
                $presenter.add()
            }
        }
        Keys.onReturnPressed: {
            $presenter.add()
        }
    }
}
