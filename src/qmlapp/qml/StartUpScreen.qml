import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import injector

import "Controls"

QmlInjector {
    id: root
    sourceComponent: Item {
        anchors.fill: parent

                property StartUpScreenPresenter $presenter
                state: $presenter.state
        states: [
            State {
                name: StartUpScreenPresenter.StateLoading
                PropertyChanges {
                    target: indicator
                    running: true
                }
                PropertyChanges {
                    target: urlFeild
                    visible: false
                }
            },
            State {
                name: StartUpScreenPresenter.StateShowDbUrlInput
                PropertyChanges {
                    target: indicator
                    running: false
                }
                PropertyChanges {
                    target: urlFeild
                    visible: true
                }
            }
        ]

        RowLayout {
            anchors.fill: parent

            Image {
                width: 36
                height: width
                sourceSize {
                    width: 36
                    height: width
                }
                source: "qrc:/qml/icons/settings_white_24dp.svg"
            }

            ColumnLayout {
                Layout.fillWidth: true
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    BusyIndicator {
                        id: indicator
                        anchors.centerIn: parent
                        width: 60
                        height: 60
                    }
                }
                RowLayout {
                    id: urlFeild
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1000

                    NamedField {
                        id: url
                        Layout.fillWidth: true
                        name: "Enter DB URL please"
                    }

                    Button {
                        text: "Save"
                        enabled: !!url.edit.text
                    }
                }

                ListView {
                    id: errorsView
                    Layout.fillWidth: true
                    height: 100
                    model: $presenter.errors
                    delegate: Text {
                        text: modelData
                        color: "white"
                    }
                    Rectangle {
                        anchors.fill: parent
                        border.width: 1
                        border.color: "gray"
                        color: "transparent"
                    }
                }
            }
        }
    }
}
