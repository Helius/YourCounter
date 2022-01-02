#include "AddNewTransactionUsecase.h"

AddNewTransactionUseCase::AddNewTransactionUseCase(IEntityRepoPtr repo)
    : QObject()
    , m_repo(repo)
{
    Q_ASSERT(m_repo);
}

void AddNewTransactionUseCase::addTransaction(const Transaction& t)
{
    Q_ASSERT(t.id.isEmpty());

    if (t.amount == 0) {
        emit transactionInvalid(InvalidReason::ZerroAmount);
        return;
    }

    if (t.categoryId.isEmpty()) {
        emit transactionInvalid(InvalidReason::EmptyCategory);
        return;
    }

    if (!checkCategoryExist(t.categoryId)) {
        emit transactionInvalid(InvalidReason::CategoryNotFound);
        return;
    }

    //TODO: get future and wait
    m_repo->transactions()->create(t);
    emit transactionAdded();
}

bool AddNewTransactionUseCase::checkCategoryExist(const QString& category)
{
    for (const auto& cat : m_repo->categories()->data()) {
        if (category == cat.id) {
            return true;
        }
    }
    return false;
}
