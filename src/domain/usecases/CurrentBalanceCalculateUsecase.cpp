#include "CurrentBalanceCalculateUsecase.h"

CurrentBalanceCalculateUsecase::CurrentBalanceCalculateUsecase(IEntityRepoPtr repo)
    :  QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
}

void CurrentBalanceCalculateUsecase::calcBalance()
{
    int64_t result = 0;
    const auto & transactions = m_repo->transactions()->data();
    for (const auto & t: transactions) {
        result += t.amount;
    }
    emit currentBalance(result);
}
