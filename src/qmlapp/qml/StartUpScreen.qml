import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import injector
import presenters

import "Controls"

QmlInjector {
    id: root

    signal startUpFinished();

    sourceComponent: Item {
        anchors.fill: parent

        property StartUpScreenPresenter $presenter
        property string st: $presenter.state

        Connections {
            target: $presenter
            function onStartUpFinished() {
                parent.startUpFinished();
            }
        }

        RowLayout {
            anchors.fill: parent

            ColumnLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height

                StackLayout {
                    id: stackLayout
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: parent.height

                    currentIndex: {
                        if(st === $presenter.StateError)
                            return 1;
                        if(st === $presenter.StateShowDbUrlInput)
                            return 2;
                        return 0;
                    }

                    // 0: loading
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        BusyIndicator {
                            id: indicator
                            anchors.centerIn: parent
                            width: 60
                            height: 60
                            running: true
                        }
                    }

                    // 1: retry
                    Item {
                        Layout.preferredWidth: implicitWidth
                        Layout.preferredHeight: implicitHeight
                        Button {
                            id: retryButton
                            anchors.centerIn: parent
                            text: "Try again"
                        }
                    }

                    // 2: enter DB url
                    Item {
                        Layout.preferredWidth: parent.width
                        Layout.fillHeight: true
                        RowLayout {
                            id: urlFeild
                            anchors.centerIn: parent
                            Layout.preferredWidth: parent.width

                            NamedField {
                                id: url
                                Layout.fillWidth: true
                                name: "Enter DB URL please"
                            }

                            Button {
                                text: "Save"
                                enabled: !!url.edit.text
                                onClicked: {
                                    $presenter.setDbUrl(url.edit.text);
                                }
                            }
                        }
                    }
                }

                ListView {
                    id: errorsView
                    Layout.fillWidth: true
                    height: 100
                    Layout.alignment: Qt.AlignBottom
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
