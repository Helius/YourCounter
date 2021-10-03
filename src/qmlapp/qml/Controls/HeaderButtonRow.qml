import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Item {
    implicitHeight: buttonRow.height + 10

    RowLayout {
    id: buttonRow
    anchors {
        verticalCenter: parent.verticalCenter
        leftMargin: 5
        rightMargin: 5
        left: parent.left
        right: parent.right
    }

    TimeScaleButtonBar {
    }

    Item {
        Layout.fillWidth: true
    }

    EditButtonBar {
    }

    }

}
