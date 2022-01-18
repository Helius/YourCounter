#pragma once

#include <QObject>
#include <usecases/CurrentBalanceCalculateUsecase.h>
#include <usecases/MonthReportUsecase.h>

class CurentBalancePresenter : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentBalance READ currentBalance NOTIFY currentBalanceChanged FINAL)
    Q_PROPERTY(QString earn MEMBER m_earn NOTIFY earnSpendChanged FINAL)
    Q_PROPERTY(QString spend MEMBER m_spend NOTIFY earnSpendChanged FINAL)

public:
    explicit CurentBalancePresenter(CurrentBalanceCalculateUsecaseUnq cbUseCase, MonthReportUsecaseUnq mpUseCase);

    QString currentBalance() const;

signals:
    void currentBalanceChanged();
    void earnSpendChanged();

private:
    void updateBalance(int64_t balance);
    void updateEarnSpend(int64_t earn, int64_t spend);

private:
    QString m_currentBalance;
    QString m_earn;
    QString m_spend;
    CurrentBalanceCalculateUsecaseUnq m_balanceUseCase;
    MonthReportUsecaseUnq m_monthReportUseCase;
};

using CurentBalancePresenterUnq = std::unique_ptr<CurentBalancePresenter>;