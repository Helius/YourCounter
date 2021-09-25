#include "addnewtransactionusecase.h"


AddNewTransactionUseCase::AddNewTransactionUseCase(ITransactionRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
}

void AddNewTransactionUseCase::addTransaction(const Transaction &t)
{
    if (abs(t.amount) > 0.01)
    {
        if (!t.category.isEmpty())
        {
            if (checkCategoryExist(t.category))
            {
                m_repo->addTransaction(std::move(t));
                emit transactionAdded();
            }
            else
            {
                if (isItNewCategory())
                {
                    m_repo->addTransaction(std::move(t));
                    emit transactionAdded();
                }
            }
        }
        else
        {
            emit transactionInvalid(InvalidReason::EmptyCategory);
        }
    }
    else
    {
        emit transactionInvalid(InvalidReason::BadAmount);
    }
}

bool AddNewTransactionUseCase::checkCategoryExist(const QString & category)
{
    for (const auto & cat: m_repo->getCategories())
    {
        if (category == cat)
        {
            return true;
        }
    }
    return false;
}

