#include "CurentBalancePresenter.h"
#include "../viewmodel/AmountVm.h"

CurentBalancePresenter::CurentBalancePresenter(CurrentBalanceCalculateUsecaseUnq balanceUseCase, MonthReportUsecaseUnq reportUseCase)
    : QObject()
    , m_balanceUseCase(std::move(balanceUseCase))
    , m_monthReportUseCase(std::move(reportUseCase))
{
    Q_ASSERT(m_balanceUseCase);
    connect(
        m_balanceUseCase.get(),
        &CurrentBalanceCalculateUsecase::currentBalance,
        this,
        &CurentBalancePresenter::updateBalance);

    m_balanceUseCase->calcBalance();

    connect(
        m_monthReportUseCase.get(),
        &MonthReportUsecase::earnSpendChanged,
        this,
        &CurentBalancePresenter::updateEarnSpend);

    m_monthReportUseCase->calcEarnSpend(QDate::currentDate());
}

QString CurentBalancePresenter::currentBalance() const
{
    return m_currentBalance;
}

void CurentBalancePresenter::updateBalance(int64_t balance)
{
    m_currentBalance = AmountVM::formatAmount(balance);
    emit currentBalanceChanged();
}

void CurentBalancePresenter::updateEarnSpend(int64_t earn, int64_t spend)
{
    m_earn = AmountVM::formatAmount(earn);
    m_spend = AmountVM::formatAmount(spend);
    emit earnSpendChanged();
}
