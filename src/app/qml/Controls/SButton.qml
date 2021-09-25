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
    implicitWidth: 70

    color: selected ? Material.highlightedButtonColor : Material.dialogColor

    radius: 5

    Text {
        id: label
        anchors.fill: parent
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: selected
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
}
