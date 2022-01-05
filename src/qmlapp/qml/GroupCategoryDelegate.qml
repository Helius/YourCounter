import QtQuick 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

Item {
    property alias groupId: list.context
    property alias groupName: list.groupName
    width: parent ? parent.width : 0
    height: list.height
    QmlInjector {
        id: list
        property string groupName
        width: parent.width
        height: view ? view.height : 0
        sourceComponent: ListView {
            id: listView
            property CategorySortedListModel $categoryModel
            property Item injector
            height: contentHeight
            model: $categoryModel

            header: Rectangle {
                height: 20
                width: 100
                color: "transparent"
                Text {
                    id: group
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    text: injector.groupName
                    font.bold: true
                    color: "white"
                }
            }

            delegate: Item {
                width: category.width + 20
                height: category.height
                Text {
                    id: category
                    height: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    text: model.categoryName
                    color: "white"
                }
            }
        }
    }
}
