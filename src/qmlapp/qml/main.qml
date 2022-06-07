import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import injector

import "Controls"

ApplicationWindow {
    id: appWindow

    width: 1210
    height: 1000
    visible: true
    title: qsTr("Your Counter")
    Material.theme: Material.Dark
    Material.accent: "#fdbb4a"
    Material.primary: "#00315f"
    Material.background: "#1C1B1F"
    Material.foreground: "#d3e3ff"
    property color errorColor: "#8C1D18"

    RowLayout {
        anchors.fill: parent
        spacing: 8
        anchors.margins: 8

        // navbar
        NavigationBar {
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: 44
        }

        // screen stack
        StackView {
            id: mainStack
            Layout.fillHeight: true
            Layout.fillWidth: true
            initialItem: StartUpScreen {
                onStartUpFinished: {
                    mainStack.push("qrc:/qml/TransactionScreen.qml")
                }
            }
        }
    }
}
