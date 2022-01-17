import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

ColumnLayout {
    property alias model: list.model
    ListView {
        id: list
        Layout.fillHeight: true
        Layout.preferredWidth: parent.width
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "gray"
            color: "transparent"
        }
        clip: true
        delegate: GroupCategoryDelegate {
            groupId: model.groupId
            groupName: model.groupName
        }

        AddNewGroupPopup {
            id: newGroupPopup
            width: 400
            height: 400
            modal: true
            focus: true
            anchors.centerIn: parent
            closePolicy: Popup.CloseOnEscape
        }
        AddNewCategoryPopup {
            id: newCategoryPopup
            width: 400
            height: 400
            modal: true
            focus: true
            anchors.centerIn: parent
            closePolicy: Popup.CloseOnEscape
        }
    }
    RowLayout {
        RoundButton {
            text: "Add Group"
            onClicked: {
                newGroupPopup.open()
            }
        }
        RoundButton {
            text: "Add Category"
            onClicked: {
                newCategoryPopup.open()
            }
        }
    }
}
