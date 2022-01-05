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
        property GroupListModel $groupModel
        property Item injector

        Connections {
            target: $presenter
            function onClosePopup() {
                injector.closePopup()
            }
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
        ListView {
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            interactive: true
            model: $groupModel
            delegate: Rectangle {
                id: groupDelegate
                color: ($presenter.groupId
                        === model.groupId) ? Material.highlightedButtonColor : Material.dialogColor
                width: name.width + 10
                height: name.height
                Text {
                    id: name
                    anchors.left: groupDelegate.left
                    anchors.leftMargin: 10
                    text: model.groupName
                    color: "white"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        $presenter.groupId = model.groupId
                    }
                }
            }
        }

        SButton {
            Layout.alignment: Qt.AlignCenter
            text: "Create category"
            onClicked: {
                $presenter.add()
            }
        }
        Keys.onReturnPressed: {
            $presenter.add()
        }
    }
}
