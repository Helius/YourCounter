import QtQuick 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenter

QmlInjector {
    id: root
    sourceComponent: ListView {

        property CategoryListModel $categoryModel

        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "red"
            color: "transparent"
        }
        anchors.fill: parent
        model: $categoryModel
        delegate: Item {
        }
    }
}
