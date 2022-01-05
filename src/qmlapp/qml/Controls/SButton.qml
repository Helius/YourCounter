import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root
    property alias text: label.text
    property bool selected: false

    signal clicked();

    implicitHeight: 30
    implicitWidth: label.width + 10

    color: (hh.hovered && !mouseArea.pressed) ? "gray"
                      :  ((selected || mouseArea.pressed) ? Material.highlightedButtonColor : Material.dialogColor)

    radius: 5

    Text {
        id: label
        height: parent ? parent.height : 0
        anchors.leftMargin: 5
        anchors.left: parent ? parent.left : undefined
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: selected
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }

    }
    HoverHandler {
        id: hh
    }
}
