import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

RowLayout {
    property alias name: text.text
    property alias edit: edit
    signal newText(var text)

    Layout.preferredWidth: 100
    spacing: 10
    Text {
        id: text
        height: 60
        color: "white"
        font.pointSize: 12
        font.weight: Font.Light
    }

    TextField {
        id: edit
        height: 60
        font.pointSize: 12
        color: "white"
        onTextEdited: {
            newText(edit.text)
        }
    }
}
