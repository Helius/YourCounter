import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import "Controls"

Popup {
    id: root
    property alias transactionId: view.context
    padding: 30
    EditTransactionView {
        id: view
        onClosePopup: root.close()
    }
}
