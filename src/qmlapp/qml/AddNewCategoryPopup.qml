import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters

import "Controls"

Popup {
    id: root

    contentItem: AddNewCategoryView {
        onClosePopup: root.close()
    }
}