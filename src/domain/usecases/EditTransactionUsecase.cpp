#include "EditTransactionUsecase.h"

EditTransactionUsecase::EditTransactionUsecase(IEntityRepoPtr repo)
    : m_repo(repo)
{
    Q_ASSERT(m_repo);
}

std::pair<Transaction, QString> EditTransactionUsecase::loadTransaction(const QString& transactionId)
{
    auto transactions = m_repo->transactions()->data();

    const auto tOpt = m_repo->transactions()->find(transactionId);

    Q_ASSERT(!!tOpt);

    m_loadedTransactionId = transactionId;
    auto categories = m_repo->categories()->data();

    Transaction result(*tOpt);

    auto categoryOpt = m_repo->categories()->find(result.categoryId);

    Q_ASSERT(!!categoryOpt);

    return std::make_pair(result, categoryOpt->name);
}

EditTransactionUsecase::EditError EditTransactionUsecase::applyChanges(const Transaction& t)
{
    if (t.id != m_loadedTransactionId) {
        return EditError::TransactionIdDiffer;
    }

    if (t.amount == 0) {
        return EditError::BadAmount;
    }

    if (t.categoryId.isEmpty()) {
        return EditError::CategoryNotFound;
    }

    if (!checkCategoryExist(t.categoryId)) {
        return EditError::CategoryNotFound;
    }

    if (!t.when.isValid() || t.when.date() > QDate::currentDate()) {
        return EditError::BadDate;
    }

    if (t.who.isEmpty()) {
        return EditError::BadOwner;
    }

    m_repo->transactions()->update(t);
    return EditError::Ok;
}

bool EditTransactionUsecase::checkCategoryExist(const QString& categoryId)
{
    for (const auto& cat : m_repo->categories()->data()) {
        if (categoryId == cat.id) {
            return true;
        }
    }
    return false;
}
