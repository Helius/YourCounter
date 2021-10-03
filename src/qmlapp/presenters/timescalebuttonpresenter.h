#ifndef TIMESCALEBUTTONPRESENTER_H
#define TIMESCALEBUTTONPRESENTER_H

#include <QObject>
#include <qmlapp/repos/idatecolumnadapter.h>

class TimeScaleBarVM {

    Q_GADGET

    Q_PROPERTY(bool daySelected MEMBER m_daySelected CONSTANT)
    Q_PROPERTY(bool weekSelected MEMBER m_weekSelected CONSTANT)
    Q_PROPERTY(bool monthSelected MEMBER m_monthSelected CONSTANT)

public:
    TimeScaleBarVM() = delete;
    TimeScaleBarVM(bool day, bool week, bool month);

public:
    bool m_daySelected;
    bool m_weekSelected;
    bool m_monthSelected;
};

class TimeScaleButtonPresenter
    : public QObject
{
    Q_OBJECT

    Q_PROPERTY(const TimeScaleBarVM & vm READ vm NOTIFY vmChanged FINAL)

public:
    TimeScaleButtonPresenter(std::shared_ptr<IDateColumnAdapter> adapter);
    const TimeScaleBarVM & vm() const { return m_viewModel; }

    Q_INVOKABLE void dayClicked();
    Q_INVOKABLE void weekClicked();
    Q_INVOKABLE void monthClicked();

signals:
    void vmChanged();

private:
    TimeScaleBarVM m_viewModel {true, false, false};
    std::shared_ptr<IDateColumnAdapter> m_adapter;
};

#endif // TIMESCALEBUTTONPRESENTER_H
