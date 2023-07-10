import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import presenters
import injector

import "Controls"

QmlInjector {
    id: root

    property string categoryId
    property string categoryText

    implicitHeight: view ? view.implicitHeight : 0
    implicitWidth: view ? view.width : 0

    function selectAll() {
        if (view) {
            view.field.edit.selectAll();
        }
    }

    sourceComponent: ColumnLayout {
        id: layout
        required property CategorySuggestModel $suggestModel
        required property Item injector
        width: 300
        spacing: 10

        Component.onCompleted: {
            Qt.callLater(function() {
                field.edit.text = injector.categoryText;
                $suggestModel.setFilterRegularExpression(injector.categoryText);
            });

        }

        NamedField {
            id: field
            name: "Category"
            onNewText: text => {
                $suggestModel.setFilterRegularExpression(text);
            }
            Keys.onReturnPressed: {
                if (list.count === 1) {
                    injector.categoryId = list.itemAtIndex(0).categoryId_
                    field.edit.text = list.itemAtIndex(0).text
                }
            }
            Button {
                text: "x"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    field.edit.text = "";
                    $suggestModel.setFilterRegularExpression("");
                    injector.categoryId = ""
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
                width: parent.width
                property string categoryId_: model.categoryId
                text: model.groupName + ": " + model.categoryName
                color: "white"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        injector.categoryId = model.categoryId
                        field.edit.text = model.categoryName
                    }
                }
            }
        }
    }
}
