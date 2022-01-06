#include "CurentBalancePresenter.h"

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
    m_currentBalance = QString("%1,%2")
                           .arg(balance / 100, 0, 10)
                           .arg(abs(balance % 100), 2, 10, QLatin1Char('0'));
    emit currentBalanceChanged();
}
