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

        property AddCategoryPresenter $presenter

        function onClosePopup() {
            parent.closePopup();
        }

        NamedField {
            id: categoryName
            name: "Category name"
            Binding {
                target: $presenter
                property: "name"
                value: categoryName.edit.text
            }
        }

        NamedField {
            id: groupName
            name: "Group name"
            Binding {
                target: $presenter
                property: "groupId"
                value: groupName.edit.text
            }
        }

        SButton {
            Layout.alignment: Qt.AlignCenter
            text: "Create group"
            onClicked: {
                $presenter.add()
            }
        }
    }
}
