#include "timescalebuttonpresenter.h"
#include <QQmlEngine>


TimeScaleButtonPresenter::TimeScaleButtonPresenter(std::shared_ptr<IDateColumnAdapter> adapter)
//    : QObject(parent)
    : m_adapter(adapter)
{
    Q_ASSERT(adapter);

    const auto updater = [this, adapter]() {
        switch(adapter->scale()) {
            case IDateColumnAdapter::TimeScale::Day:
                m_viewModel = {true, false, false};
                break;
            case IDateColumnAdapter::TimeScale::Week:
                m_viewModel = {false, true, false};
                break;
            case IDateColumnAdapter::TimeScale::Month:
                m_viewModel = {false, false, true};
                break;
        }
        emit vmChanged();
    };

    connect(adapter.get(), &IDateColumnAdapter::scaleChanged, this, updater);
    updater();
}

void TimeScaleButtonPresenter::dayClicked()
{
    m_adapter->setScale(IDateColumnAdapter::TimeScale::Day);
}

void TimeScaleButtonPresenter::weekClicked()
{
    m_adapter->setScale(IDateColumnAdapter::TimeScale::Week);
}

void TimeScaleButtonPresenter::monthClicked()
{
    m_adapter->setScale(IDateColumnAdapter::TimeScale::Month);
}

TimeScaleBarVM::TimeScaleBarVM(bool day, bool week, bool month)
    : m_daySelected(day)
    , m_weekSelected(week)
    , m_monthSelected(month)
{}
