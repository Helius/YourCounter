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
                console.log("startup finished");
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
                        if(st === $presenter.StateShowInputs)
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

                            ColumnLayout {

                                NamedField {
                                    id: url
                                    Layout.fillWidth: true
                                    name: "DB URL:"
                                    edit.text: $presenter.dbUrl
                                    onNewText: function(newText) { $presenter.dbUrl = newText };
                                }
                                NamedField {
                                    id: token
                                    Layout.fillWidth: true
                                    name: "App token"
                                    edit.text: $presenter.appToken
                                    onNewText: function(newText) { $presenter.appToken = newText };
                                }
                                NamedField {
                                    id: name
                                    Layout.fillWidth: true
                                    name: "Name:"
                                    edit.text: $presenter.userName
                                    onNewText: function(newText) { $presenter.userName = newText };
                                }
                                NamedField {
                                    id: passwd
                                    Layout.fillWidth: true
                                    name: "Passwd:"
                                    edit.text: $presenter.passwd
                                    onNewText: function(newText) { $presenter.passwd = newText };
                                }
                                RowLayout {
                                    Layout.alignment: Qt.AlignCenter
                                    spacing: 20
                                    Button {
                                        text: "Login"
                                        enabled: $presenter.signEnabled;
                                        onClicked: {
                                            $presenter.signIn();
                                        }
                                    }
                                    Button {
                                        text: "Sign up"
                                        enabled: $presenter.signEnabled;
                                        onClicked: {
                                            $presenter.signUp();
                                        }
                                    }
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
