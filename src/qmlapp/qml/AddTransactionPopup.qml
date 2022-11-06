import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Popup {
    id: root
    padding: 30
    AddTransactionView {
        id: view
        onClosePopup: root.close()
    }
    onOpened: {
        view.init();
    }
}
