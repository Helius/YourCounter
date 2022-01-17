#include "EditTransactionUsecase.h"

EditTransactionUsecase::EditTransactionUsecase(IEntityRepoPtr repo)
    : m_repo(repo)
{
    Q_ASSERT(m_repo);
}

std::pair<Transaction, QString> EditTransactionUsecase::loadTransaction(const QString& transactionId)
{
    auto transactions = m_repo->transactions()->data();

    auto it = std::find_if(transactions.begin(), transactions.end(),
        [transactionId](const auto& t) {
            return t.id == transactionId;
        });

    Q_ASSERT(it != transactions.cend());

    m_loadedTransactionId = transactionId;
    auto categories = m_repo->categories()->data();

    Transaction result(*it);

    auto categoryIt = std::find_if(categories.cbegin(), categories.cend(), [categoryId = result.categoryId](const auto& c) {
        return c.id == categoryId;
    });

    Q_ASSERT(categoryIt != categories.cend());

    return std::make_pair(result, categoryIt->name);
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
