import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Popup {
    id: root
    padding: 30
    property var transactionData
    
    function init(data) {
        transactionData = data;
        view.init(data)
    }
    
    AddTransactionView {
        id: view
        onClosePopup: root.close()
    }
    
    onOpened: {
        if (!transactionData) {
            view.init("");
        }
    }
}
