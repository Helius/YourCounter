import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: root
    property alias amount: lable.text
    property alias background: root.color
    property bool current: false
    implicitHeight: 22
    implicitWidth: 55
    border.width: current ? 1 : 0
    border.color: "gray"
    Text {
        id: lable
        anchors.fill: parent
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pointSize: 12
        font.weight: Font.Light
    }
}
