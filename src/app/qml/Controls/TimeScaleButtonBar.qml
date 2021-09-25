import QtQuick 2.0
import presenters
import injector

QmlInjector {

    sourceComponent: Component {

    Item {

        property TimeScaleButtonPresenter $presenter

        implicitWidth: row.width
        implicitHeight: row.height

        Row {
        id: row
        spacing: 10
        SButton {
            text: "Day"
            selected: $presenter.vm.daySelected
            onClicked: $presenter.dayClicked()
        }
        SButton {
            text: "Week"
            selected: $presenter.vm.weekSelected
            onClicked: $presenter.weekClicked()
        }
        SButton {
            text: "Month"
            selected: $presenter.vm.monthSelected
            onClicked: $presenter.monthClicked()
        }
        }
    }
    }
}
