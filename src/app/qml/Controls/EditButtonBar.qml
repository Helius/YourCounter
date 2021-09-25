import QtQuick 2.0

Item {
    implicitWidth: row.width
    implicitHeight: row.height
    Row {
        id: row
        spacing: 10
        SButton {
            text: "Edit"
        }

        SButton {
            text: "Add"
        }
    }
}
