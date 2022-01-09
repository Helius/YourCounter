#include "CurentBalancePresenter.h"
#include "../viewmodel/AmountVm.h"

CurentBalancePresenter::CurentBalancePresenter(CurrentBalanceCalculateUsecaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);
    connect(m_usecase.get(), &CurrentBalanceCalculateUsecase::currentBalance, this, &CurentBalancePresenter::updateBalance);
    m_usecase->calcBalance();
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
