import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

QmlInjector {
    id: root
    function setCategoryId(categoryId) {
        view.$suggestModel.setCategoryId(categoryId);
    }
    property string categoryId
    implicitHeight: view ? view.implicitHeight : 0
    implicitWidth: view ? view.width : 0
    sourceComponent: ColumnLayout {
        id: layout
        required property CategorySuggestModel $suggestModel
        required property Item injector
        width: 300
        spacing: 10
        NamedField {
            id: field
            name: "Category"
            onNewText: text => {
                $suggestModel.setFilterFixedString(text);
            }
            Keys.onReturnPressed: {
                if (list.count === 1) {
                    injector.categoryId = list.itemAtIndex(0).catId
                    field.edit.text = list.itemAtIndex(0).text
                }
            }
        }
        ListView {
            id: list
            width: field.width
            Layout.leftMargin: 70
            height: 100
            model: $suggestModel
            delegate: Text {
//                property string catId: model.categoryId
                text: model.categoryName
                color: "white"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        injector.categoryId = model.categoryId
                        field.edit.text = model.text
                    }
                }
            }
        }
    }
}
