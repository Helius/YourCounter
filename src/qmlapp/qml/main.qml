import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import injector

import "Controls"

ApplicationWindow {

    width: 1200
    height: 1000
    visible: true
    title: qsTr("Your Counter")
    Material.theme: Material.Dark

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
