import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

Rectangle {
    border.width: 1
    border.color: "#938F99"
    color: Material.background
    Material.elevation: 1
    radius: 4

    Column {
        height: parent.height
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 8
            leftMargin: 4
            rightMargin: 4
        }
        spacing: 24



    Image {
        width: 36
        height: width
        sourceSize {
            width: 36
            height: width
        }
        source: "qrc:/qml/icons/add_shopping_cart_white_24dp.svg"
    }
    Image {
        width: 36
        height: width
        sourceSize {
            width: 36
            height: width
        }
        source: "qrc:/qml/icons/align_horizontal_left_white_24dp.svg"
    }
    Image {
        width: 36
        height: width
        sourceSize {
            width: 36
            height: width
        }
        source: "qrc:/qml/icons/settings_white_24dp.svg"
    }
    }
}
