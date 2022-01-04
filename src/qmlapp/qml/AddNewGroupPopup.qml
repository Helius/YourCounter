import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

Popup {
    id: root

    contentItem: AddNewGroupView {
        onClosePopup: root.close()
    }
}