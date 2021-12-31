#include "AddNewTransactionUsecase.h"

AddNewTransactionUseCase::AddNewTransactionUseCase(IEntityRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
}

void AddNewTransactionUseCase::addTransaction(const Transaction& t, bool)
{
    if (t.amount != 0) {
        //        if (!t.category.isValid())
        //        {
        //            if (checkCategoryExist(t.category) || allowNewCategory)
        //            {
        //                m_repo->addTransaction(std::move(t));
        //                emit transactionAdded();
        //            }
        //            else
        //            {
        //                emit isItNewCategory();
        //            }
        //        }
        //        else
        //        {
        emit transactionInvalid(InvalidReason::EmptyCategory);
        //        }
    } else {
        emit transactionInvalid(InvalidReason::ZerroAmount);
    }
}

bool AddNewTransactionUseCase::checkCategoryExist(const Category&)
{
    //    for (const auto & cat: m_repo->getCategories())
    //    {
    //        if (category == cat)
    //        {
    //            return true;
    //        }
    //    }
    return false;
}
