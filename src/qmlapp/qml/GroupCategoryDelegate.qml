import QtQuick 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts
import "Controls"

import injector
import presenters

Item {
    property alias groupId: list.context
    property alias groupName: list.groupName
    width: parent.width
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

            header:
                Rectangle {
                height: 30
                border.width: 1
                border.color: "red"
                color: "green"
                Text {
                    text: injector.groupName
                    color: "white"
                }
            }

            delegate:
                Text {
                height: 20
                width: parent.width
                text: model.categoryName
            }
        }
    }
}
